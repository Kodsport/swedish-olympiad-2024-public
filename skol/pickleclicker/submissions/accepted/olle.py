#!/usr/bin/env python3

n,t = [int(i) for i in input().split()]

p = [None]*n
c = [None]*n

for i in range(n):
    p[i], c[i] = [int(k) for k in input().split()]


# If the largest production possible at round X is P
# then there are at most (T - X) / P rounds left
# => ... => the DP has at most O(T log T) states 

dp = [{} for i in range(t+2)]
dp[1][p[0]] = p[0]

for round in range(1, t+1):
    for production in dp[round].keys():
        money_in_pocket = dp[round][production]
        if money_in_pocket >= t:
            print(round)
            exit(0)
        if production not in dp[round+1].keys():
            dp[round+1][production] = money_in_pocket + production
        else:
            dp[round+1][production] = max(
                money_in_pocket + production,
                dp[round+1][production]
            )
        for building in range(n):
            if c[building] > money_in_pocket:
                continue
            new_production = production + p[building]
            if new_production not in dp[round+1].keys():
                dp[round+1][new_production] = money_in_pocket + new_production - c[building]
            else:
                dp[round+1][new_production] = max(
                    dp[round+1][new_production], 
                    money_in_pocket + new_production - c[building]
                )
