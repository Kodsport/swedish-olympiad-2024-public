#!/usr/bin/env python3
#
# Testing tool for the task KATT:s and rats.
#
# Usage:
#
#   python3 testing_tool.py [--silent] program... <input.txt
#
# input.txt uses the following format:
#
# N K
# a1 b1
# a2 b2
# ...
# a_{n-1} b_{n-1}
# x_1 x_2 ... x_K
# t_1 t_2 ... t_K
#
#
# For example, if you have a Python solution that you would run using
# "python3 file.py", you could invoke the testing tool with:
#
#   python3 testing_tool.py python3 file.py < input.txt
#
# where input.txt is a file that contains e.g.
#
# 3 1
# 1 2
# 2 3
# 1
# 3
#
# This input corresponds to sample case 1.
# If --silent is passed, the communication output will not be printed.
#
# The tool is provided as-is, and you should feel free to make
# whatever alterations or augmentations you like to it.
#

import subprocess
import sys

def error(msg):
    print("ERROR:", msg)
    sys.exit(1)

def main():
    silent = False
    args = sys.argv[1:]
    if args and args[0] == "--silent":
        args = args[1:]
        silent = True
    if not args or args == ["--help"] or args == ["-h"]:
        print("Usage:", sys.argv[0], "[--silent] program... <input.txt")
        sys.exit(0)
    
    try:
        n, k = [int(i) for i in input().split()]
        g = [[] for i in range(n)]
    except Exception:
        error("bad input format: failed to parse first line as two integers")
    for i in range(n-1):
        try:
            line = input()
        except Exception:
            error("bad input format: too few lines")
        try:
            a, b = [int(i)-1 for i in line.split()]
            assert 0 <= a < n and 0 <= b < n and a != b
            g[a].append(b)
            g[b].append(a)
        except Exception:
            error(f"bad input format: line '{line}' does not contain 2 different integers in range [1, n]")
    try:
        line = input()
    except:
        error("bad input format: too few lines")
    try:
        rats = [int(i)-1 for i in line.split()]
        assert(len(rats) == len(set(rats)) and len(rats) == k)
        assert(all([0 <= r < n for r in rats]))
    except:
        error(f"Bad rats: Expected K different integers in interval [1, n]")
    try:
        line = input()
    except:
        error("bad input format: too few lines")
    try:
        targets = [int(i)-1 for i in line.split()]
        assert(len(targets) == len(set(targets)) and len(targets) == k)
        assert(all([0 <= r < n for r in targets]))
    except:
        error(f"Bad targets: Expected K different integers in interval [1, n]")

                
    proc = subprocess.Popen(args, stdin=subprocess.PIPE, stdout=subprocess.PIPE)
    if not silent:
        print(f"[*] Running with N = {n}, K = {k}")

    proc.stdin.write(f"{n} {k}\n".encode("utf8"))
    proc.stdin.flush()

    rs = " ".join([str(i+1) for i in sorted(rats)]) + "\n"
    ts = " ".join([str(i+1) for i in sorted(targets)]) + "\n"
    proc.stdin.write(rs.encode("utf8"))
    proc.stdin.flush()
    proc.stdin.write(ts.encode("utf8"))
    proc.stdin.flush()
    if not silent:
        print(f"< {n} {k}")
        print("<",rs, end="")
        print("<",ts, end="")

    MAX_QUERIES = 25000
    queries = 0

    while True:
        command = proc.stdout.readline().decode("utf8")
        command = command.strip()
        line = command

        if queries > MAX_QUERIES:
            error("[*] Wrong answer: Too many queries")

        if not silent:
            print(f"> {command}")

        if command == "activate!":
            if set(rats) == set(targets):
                print(f"[*] OK: Caught all rats. queries used: {queries}.")
                exit(0)
            else:
                error("f[*] Wrong answer: Activated traps while not all rats caught.")

        queries += 1
        try:
            command = [int(i) for i in command.split()]
            M = command[0]
            sonar = command[1:]
            sonar = [int(i)-1 for i in sonar]
            assert(len(sonar) == M)
            assert(len(sonar) == len(set(sonar)))
            assert(all([0 <= x < n for x in sonar]))
        except:
            error(f"Invalid query: '{line}'")
                

        dist = [-1] * n
        queue = []
        for r in sonar:
            dist[r] = 0
            queue.append(r)
            

        while queue:
            x = queue.pop(0)
            for nei in g[x]:
                if dist[nei] == -1:
                    dist[nei] = dist[x] + 1
                    queue.append(nei)

        occupied = [False]*n
        for r in rats:
            occupied[r] = True
        for r in sorted(rats):
            best_score = dist[r]
            best = r
            for nei in g[r]:
                if occupied[nei]: continue
                if (dist[nei] > best_score) or (dist[nei] == best_score and nei < best and best != r):
                    best = nei
                    best_score = dist[nei]
            occupied[r] = False
            occupied[best] = True

        rats = [r for r in range(n) if occupied[r]]
        rs = " ".join([str(i+1) for i in sorted(rats)]) + "\n"
        
        proc.stdin.write(rs.encode("utf8"))
        proc.stdin.flush()
        if not silent:
            print("<",rs, end="")
        

if __name__ == "__main__":
    main()