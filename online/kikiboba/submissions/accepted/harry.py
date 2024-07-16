#!/usr/bin/env python3

s = input()

if s.count("b") == s.count("k") == 0:
    print("none")
elif s.count("b") == s.count("k"):
    print("boki")
elif s.count("b") > s.count("k"):
    print("boba")
else:
    print("kiki")
