#!/usr/bin/env python3
"""
Benchmark: redis-clone vs real Redis
Clone speaks a simple line protocol (port 8000).
Redis speaks RESP (port 6379) — no pip installs needed.

Usage:
  1. Start your clone:   ./bin/kvserver
  2. Start Redis:        redis-server   (optional)
  3. Run:                python3 benchmark.py [N]
"""

import socket
import time
import sys

N = int(sys.argv[1]) if len(sys.argv) > 1 else 10_000


# ── Buffered reader (works for both protocols) ──────────────────────────────

class Reader:
    def __init__(self, sock):
        self.sock = sock
        self.buf = b""

    def readline(self):
        while b"\n" not in self.buf:
            chunk = self.sock.recv(4096)
            if not chunk:
                raise ConnectionError("connection closed")
            self.buf += chunk
        idx = self.buf.index(b"\n")
        line, self.buf = self.buf[:idx + 1], self.buf[idx + 1:]
        return line

    def read_bytes(self, n):
        while len(self.buf) < n:
            chunk = self.sock.recv(4096)
            if not chunk:
                raise ConnectionError("connection closed")
            self.buf += chunk
        data, self.buf = self.buf[:n], self.buf[n:]
        return data


# ── Clone protocol: "+OK\n" / "+<value>\n" / "-nil\n" ───────────────────────

def clone_recv(reader):
    reader.readline()  # consume the one-line response


def clone_set(reader, sock, key, value):
    sock.sendall(f"SSET {key} {value}\n".encode())
    clone_recv(reader)


def clone_get(reader, sock, key):
    sock.sendall(f"GET {key}\n".encode())
    clone_recv(reader)


# ── Redis RESP protocol ──────────────────────────────────────────────────────

def resp_encode(*args):
    msg = f"*{len(args)}\r\n"
    for a in args:
        a = str(a)
        msg += f"${len(a)}\r\n{a}\r\n"
    return msg.encode()


def resp_recv(reader):
    line = reader.readline()
    prefix = chr(line[0])
    if prefix in ('+', '-', ':'):
        return
    if prefix == '$':
        n = int(line[1:].strip())
        if n >= 0:
            reader.read_bytes(n + 2)  # bulk string + \r\n
    elif prefix == '*':
        count = int(line[1:].strip())
        for _ in range(count):
            resp_recv(reader)


def redis_set(reader, sock, key, value):
    sock.sendall(resp_encode("SET", key, value))
    resp_recv(reader)


def redis_get(reader, sock, key):
    sock.sendall(resp_encode("GET", key))
    resp_recv(reader)


# ── Benchmark runner ─────────────────────────────────────────────────────────

def run(label, host, port, set_fn, get_fn):
    print(f"--- {label} ---")
    try:
        sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        sock.connect((host, port))
        reader = Reader(sock)
    except OSError as e:
        print(f"  Could not connect to {host}:{port} — {e}\n")
        return

    try:
        t0 = time.perf_counter()
        for i in range(N):
            set_fn(reader, sock, f"k{i}", f"v{i}")
        set_elapsed = time.perf_counter() - t0

        t0 = time.perf_counter()
        for i in range(N):
            get_fn(reader, sock, f"k{i}")
        get_elapsed = time.perf_counter() - t0

        print(f"  SET  {N / set_elapsed:>9,.0f} ops/sec  ({set_elapsed * 1000:.1f} ms)")
        print(f"  GET  {N / get_elapsed:>9,.0f} ops/sec  ({get_elapsed * 1000:.1f} ms)")
    except Exception as e:
        print(f"  Error during benchmark: {e}")
    finally:
        sock.close()
    print()


# ── Main ─────────────────────────────────────────────────────────────────────

print(f"Benchmarking with {N:,} sequential ops per command\n")

run("Redis Clone  (port 8000)", "127.0.0.1", 8000, clone_set, clone_get)
run("Real Redis   (port 6379)", "127.0.0.1", 6379, redis_set, redis_get)
