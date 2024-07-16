#!/usr/bin/env python3

n = int(input())
t = [*input()]

m = int(input())
words = [input() for _ in range(m)]

BFS = []
depth = []

for word in words:
    for i in range(len(word)):
        if word[i] != t[i]:
            break
    else:

        if len(word) == n:
            print(1)
            exit()
        
        BFS.append(len(word))
        depth.append(1)

visited=[0]*(n+1)

counter=-1
for curr in BFS:
    counter+=1
    for word in words:
        if len(word) > n-curr:#Om ordet har fler bokstäver än vad som får plats just nu så kan det aldrig vara korrekt
            continue

        for i in range(len(word)):
            if word[i]!=t[curr+i]:
                break
        else:
            if len(word)+curr == n:
                print(depth[counter]+1)
                exit()
            
            BFS.append(len(word)+curr)
            depth.append(depth[counter]+1)

