#!/usr/bin/python3
import sys
sys.setrecursionlimit(10000)


#From PyRival
#https://github.com/cheran-senthil/PyRival/blob/master/pyrival/graphs/lca.py 
class RangeQuery:
    def __init__(self, data, func=min):
        self.func = func
        self._data = _data = [list(data)]
        i, n = 1, len(_data[0])
        while 2 * i <= n:
            prev = _data[-1]
            _data.append([func(prev[j], prev[j + i]) for j in range(n - 2 * i + 1)])
            i <<= 1

    def query(self, begin, end):
        depth = (end - begin).bit_length() - 1
        return self.func(self._data[depth][begin], self._data[depth][end - (1 << depth)])


class LCA:
    def __init__(self, root, graph):
        self.time = [-1] * len(graph)
        self.path = [-1] * len(graph)
        P = [-1] * len(graph)
        t = -1
        dfs = [root]
        while dfs:
            node = dfs.pop()
            self.path[t] = P[node]
            self.time[node] = t = t + 1
            for nei in graph[node]:
                if self.time[nei] == -1:
                    P[nei] = node
                    dfs.append(nei)
        self.rmq = RangeQuery(self.time[node] for node in self.path)

    def __call__(self, a, b):
        if a == b:
            return a
        a = self.time[a]
        b = self.time[b]
        if a > b:
            a, b = b, a
        return self.path[self.rmq.query(a, b)]

#From PyRival
#https://github.com/cheran-senthil/PyRival/blob/master/pyrival/data_structures/FenwickTree.py
class FenwickTree:
    def __init__(self, x):
        """transform list into BIT"""
        self.bit = x
        for i in range(len(x)):
            j = i | (i + 1)
            if j < len(x):
                x[j] += x[i]

    def update(self, idx, x):
        """updates bit[idx] += x"""
        while idx < len(self.bit):
            self.bit[idx] += x
            idx |= idx + 1

    def query(self, end):
        """calc sum(bit[:end])"""
        x = 0
        while end:
            x += self.bit[end - 1]
            end &= end - 1
        return x

    def findkth(self, k):
        """Find largest idx such that sum(bit[:idx]) <= k"""
        idx = -1
        for d in reversed(range(len(self.bit).bit_length())):
            right_idx = idx + (1 << d)
            if right_idx < len(self.bit) and k >= self.bit[right_idx]:
                idx = right_idx
                k -= self.bit[idx]
        return idx + 1

def traverse(root,graph):
    visited = [0]*len(graph)
    order = []
    visited[root] = 1

    def DFS(curr):
        order.append(curr)
        for nxt in graph[curr]:
            if visited[nxt]:
                continue
            visited[nxt] = 1
            DFS(nxt)
        order.append(curr)
    
    DFS(root)
    return order

n,c = map(int,input().split())

edges = [[] for _ in range(n)]
for _ in range(n-1):
    a,b = map(lambda x: int(x)-1,input().split())
    edges[a].append(b)
    edges[b].append(a)

order = traverse(0,edges)

fenInd = [[] for _ in range(n)]
for i in range(len(order)):
    fenInd[order[i]].append(i)

cars = [[*map(lambda x: int(x)-1,input().split())] for _ in range(c)]
data = [0]*(2*n)

for a,b in cars:
    currInd = a
    data[fenInd[currInd][0]]=1
    data[fenInd[currInd][1]]=-1

fen = FenwickTree(data)
lca = LCA(0,edges)

def query(a,b):
    #Calculate the sum from a to b
    #Is it possible to go from node a to node b?
    temp = 0
    temp += fen.query(fenInd[a][0]+1)
    temp += fen.query(fenInd[b][0]+1)
    temp -= fen.query(fenInd[lca(a,b)][0]+1)
    temp -= fen.query(fenInd[lca(a,b)][0])

    assert temp>0 #since the node a should be activated

    if temp == fen.query(fenInd[a][0]+1) - fen.query(fenInd[a][0]):
        return 1 #yes it is possible
    return 0 #no it is not

def move(a,b):
    #Move car from node a to node b
    fen.update(fenInd[a][0],-1)
    fen.update(fenInd[a][1],1)

carsRemaining = [*range(c)]

output = []
carsRemaining.reverse()
while carsRemaining:
    for i in range(len(carsRemaining)-1,-1,-1):
        a,b = cars[carsRemaining[i]]
        if query(a,b):
            output.append(carsRemaining[i]+1)
            carsRemaining.pop(i)
            move(a,b)
            break
    else:
        print("No")
        exit()

print("Yes")
print(*output)

