#!/usr/bin/python3
n,t,s = [int(x) for x in input().split(" ")]

intervals = []
for _ in range(n):
    l,r=[int(x) for x in input().split(" ")]
    intervals.append((l,r))


r=0 # Index of the first interval to not be included fully
ans=0
cur=0
for i,interval in enumerate(intervals):
    r=max(r,i)
    l=interval[0]
    while r<n and l+s-1>=intervals[r][1]:
        cur+=intervals[r][1]-intervals[r][0]+1
        r+=1
    ans=max(ans,cur+max(0,l+s-1-intervals[r-1][1]))
    if r!=i:
        cur-=interval[1]-interval[0]+1

print(s-ans)