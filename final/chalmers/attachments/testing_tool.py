#!/usr/bin/env python3
#
# Testing tool for the task The Dark Chambers of Chalmers.
#
# Usage:
#
#   python3 testing_tool.py [--silent] program... <input.txt
#
# input.txt uses the following format:
#
#   N
#   r_{1,1}
#   r_{2,1} r_{2,2}
#   r_{3,1} r_{3,2} r_{3,3} 3_{3,4}
#   ...   
#   r_{N,1} ... r_{N, 2^{N+1}}
#   A
#   s_1 ... s_A
#   B
#   g_1 ... g_B
#
# where the basement has N floors, and the value r_{i, j} tells you if there is a room in the j:th position of the i:th floor.
# The values of A and B are depths of the starting and goal positions, and s and g are the paths down from the basement to them. 
# s_i = 0 if the i:th step is a "downleft" step.
#
#
# For example, if you have a Python solution that you would run using
# "python3 file.py", you could invoke the testing tool with:
#
#   python3 testing_tool.py python3 file.py < input.txt
#
# where input.txt is a file that contains e.g.
#
# 4
# 1
# 1 1
# 1 1 0 1
# 1 1 1 0 0 0 1 0
# 2
# 0 0
# 3
# 1 1 0
#
# This input corresponds to sample case 1.
# If --silent is passed, the communication output will not be printed.
#
# The tool is provided as-is, and you should feel free to make
# whatever alterations or augmentations you like to it.
#

import subprocess
import sys
import heapq

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
        n = int(input())
        r = []
    except Exception:
        error("bad input format: failed to parse first line as integer")
    for i in range(n):
        try:
            line = input()
        except Exception:
            error("bad input format: too few lines")
        try:
            line = [int(x) for x in line.split()]
            assert len(line) == 1<<i
            assert all([x == 0 or x == 1 for x in line])
            r.append(line)
        except Exception:
            error(f"bad input format: line '{line}' does not contain 2^depth integers either 0 or 1")
    try:
        A = input()
    except:
        error("expected length of path to start position")
    try:
        A = int(A)
        assert(A >= 0 and A < n)
    except:
        error(f"Expected length of path to start to be integer between 0 and {n-1} inclusive")
    try:
        path = input()
    except:
        error("expected path to start position")
    try:
        path = [int(i) for i in path.split()]
        assert(len(path) == A)
        assert(all([x == 0 or x == 1 for x in path]))
    except:
        error("invalid path to start position")
    try:
        pos_level = 0
        pos_offset = 0
        for i in range(A):
            pos_level += 1
            pos_offset *= 2
            if path[i]:
                pos_offset += 1
        assert(r[pos_level][pos_offset] == 1)
    except:
        error("path to start leads to non-room")
    try:
        B = input()
    except:
        error("expected length of path to goal position")
    try:
        B = int(B)
        assert(B >= 0 and B < n)
    except:
        error(f"Expected length of path to goal to be integer between 0 and {n-1} inclusive")
    try:
        goal = input()
    except:
        error("expected path to goal position")
    try:
        goal = [int(i) for i in goal.split()]
        assert(len(goal) == B)
        assert(all([x == 0 or x == 1 for x in goal]))
    except:
        error("invalid path to goal position")    
    try:
        goal_level = 0
        goal_offset = 0
        for i in range(B):
            goal_level += 1
            goal_offset *= 2
            if goal[i]:
                goal_offset += 1    
        assert(r[goal_level][goal_offset] == 1)
    except:
        error("path to goal leads to non-room")

    
    def CGDL(pl, po):
        if pl == n-1:
            return False
        return r[pl+1][po*2]
    def CGDR(pl, po):
        if pl == n-1:
            return False
        return r[pl+1][1+po*2]
    def CGR(pl, po):
        if po == (1<<pl) - 1:
            return False
        return r[pl][po+1]
    def CGL(pl, po):
        if po == 0:
            return False
        return r[pl][po-1]
    def CGU(pl, po):
        return pl != 0
    def GDL(pl, po):
        pl += 1
        po *= 2
        return pl, po
    def GDR(pl, po):
        pl += 1
        po = 2*po + 1
        return pl, po
    def GR(pl, po):
        po += 1
        return pl, po
    def GL(pl, po):
        po -= 1
        return pl, po
    def GU(pl, po):
        pl -= 1
        po //= 2
        return pl, po
    def info(pl, po):
        return "".join(
        ["1" if x(pl,po) else "0" for x in 
            [CGU, CGR, CGDR, CGDL, CGL]
        ]
        )
    def d(pl,po):
        v = [CGU, CGR, CGDR, CGDL, CGL]
        m = [GU, GR, GDR, GDL, GL]
        c = [1, 0, 1, 1, 0]
        q = [((0,0),(pl,po))]
        v_ = set()
        while q:
            d,p=heapq.heappop(q)
            pl,po = p
            if (pl,po) in v_:
                continue
            if pl == goal_level and po == goal_offset:
                return d[1]
            v_.add((pl,po))
            for i in range(5):
                if not v[i](pl,po):
                    continue
                nl, no = m[i](pl,po)
                _,__ = d
                _ += c[i]
                __ += 1
                heapq.heappush(q, ((_, __), (nl, no)))
                
    proc = subprocess.Popen(args, stdin=subprocess.PIPE, stdout=subprocess.PIPE)
    if not silent:
        print(f"[*] Running with N = {n}")

    proc.stdin.write(f"{info(pos_level, pos_offset)}\n".encode("utf8"))
    proc.stdin.flush()
    print(f"< {info(pos_level, pos_offset)}")

    app_calls = 0
    walk_calls = 0

    while True:
        command = proc.stdout.readline().decode("utf8")
        command = command.strip()

        if app_calls > 500:
            error("[*] Wrong answer: Too many app calls")
        if walk_calls > 5000:
            error("[*] Wrong answer: Too many walk calls")

        if not silent:
            print(f"> {command}")
        if command == "up":
            if CGU(pos_level, pos_offset):
                pos_level, pos_offset = GU(pos_level, pos_offset)
            else:
                error("tried to go up when not possible")
        elif command == "right":
            if CGR(pos_level, pos_offset):
                pos_level, pos_offset = GR(pos_level, pos_offset)
            else:
                error("tried to go right when not possible")
        elif command == "downright":
            if CGDR(pos_level, pos_offset):
                pos_level, pos_offset = GDR(pos_level, pos_offset)
            else:
                error("tried to go downright when not possible")
        elif command == "downleft":
            if CGDL(pos_level, pos_offset):
                pos_level, pos_offset = GDL(pos_level, pos_offset)
            else:
                error("tried to go downleft when not possible")
        elif command == "left":
            if CGL(pos_level, pos_offset):
                pos_level, pos_offset = GL(pos_level, pos_offset)
            else:
                error("tried to go left when not possible")
        elif command == "app":
            app_calls += 1
            if not silent:
                print(f"< {d(pos_level, pos_offset)}")
            proc.stdin.write(f"{d(pos_level, pos_offset)}\n".encode("utf8"))
            proc.stdin.flush()
        elif command == "here":
            if d(pos_level, pos_offset) == 0:
                print(f"[*] OK: Found the goal room. App calls used: {app_calls}. Walks made: {walk_calls}")
                exit(0)
            else:
                print("f[*] Wrong answer: Said here when not here")
                exit(0)
        else:
            print(f"[*] Wrong answer: invalid command '{command}'")
            exit(0)
        if command in ["up", "right", "downright", "downleft", "left"]:
            walk_calls += 1
            if not silent:
                print(f"< {info(pos_level, pos_offset)}")
            proc.stdin.write(f"{info(pos_level, pos_offset)}\n".encode("utf8"))
            proc.stdin.flush()
        

if __name__ == "__main__":
    main()