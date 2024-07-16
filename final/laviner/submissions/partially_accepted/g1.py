#!/usr/bin/python3

n, k = map(int, input().split())

print(-((k-n) // (k + 1))) #ceil((m-k)/(k+1))
