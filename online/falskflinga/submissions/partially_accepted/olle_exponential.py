#!/usr/bin/python3

n = int(input())
pattern = [[int(x) for x in input()] for i in range(n)]
half = n//2

def de_transform(x,y):
    return [(x,y), (y,x), (x,-y), (y,-x), (-x,y), (-y,x), (-x,-y), (-y,-x)]

def get_solution(vis):
    sol = [[0]*n for i in range(n)]
    for _ in vis:
        x,y=_
        for _x,_y in de_transform(x,y):
            sol[half-_y][half+_x] = 1
    return sol

def print_solution(p):
    [print("".join([str(i) for i in row])) for row in p]
    print()

def valid_solution(p):
    def has_2_squares(p):
        for i in range(n-1):
            for j in range(n-1):
                if p[i][j]+p[i+1][j]+p[i][j+1]+p[i+1][j+1] == 4:
                    return True
        return False
    
    if has_2_squares(p):
        return False

    def get_neighbors(i,j):
        if i < n - 1:
            yield (i+1,j)
        if i > 0:
            yield (i-1,j)
        if j < n - 1:
            yield (i,j+1)
        if j > 0:
            yield (i,j-1)
    
    def get_neighbors_diagonal(i,j):
        for di in range(-1, 2):
            for dj in range(-1, 2):
                if di == 0 and dj == 0:
                    continue
                ni, nj = i+di, j+dj
                if ni >= 0 and ni < n and nj >= 0 and nj < n:
                    yield (ni,nj)
    
    def has_crooks(p):
        for i in range(n):
            for j in range(n):
                if p[i][j] == 0:
                    continue
                white_neighbors = [(_i,_j) for _i,_j in get_neighbors(i,j) if p[_i][_j]==1]
                if len(white_neighbors) != 2:
                    continue
                _1,_2 = white_neighbors
                i1,j1 = _1
                i2,j2 = _2
                if not (i1+i2 == 2*i and j1+j2 == 2*j):
                    return True
        return False

    if has_crooks(p):
        return False
    
    def connected(p):
        def dfs(i, j, vis):
            vis[i][j] = 1
            for _i,_j in get_neighbors(i, j):
                if p[_i][_j] == 0:
                    continue
                if vis[_i][_j]:
                    continue
                dfs(_i,_j,vis)
        vis = [[0]*n for i in range(n)]
        dfs(half,half,vis)
        for i in range(n):
            for j in range(n):
                if vis[i][j] != p[i][j]:
                    return False
        return True

    if not connected(p):
        return False
    
    def black_connected(p):
        ci, cj = None, None
        for i in range(n):
            for j in range(n):
                if p[i][j] == 0:
                    ci, cj = i, j
        def dfs(i, j, vis):
            vis[i][j] = 1
            for _i,_j in get_neighbors_diagonal(i, j):
                if p[_i][_j] == 1:
                    continue
                if vis[_i][_j]:
                    continue
                dfs(_i,_j,vis)
        vis = [[0]*n for i in range(n)]
        dfs(ci, cj, vis)
        for i in range(n):
            for j in range(n):
                if vis[i][j] == 0 and p[i][j] == 0:
                    return False
        return True
    
    if not black_connected(p):
        return False
    
    return True

squares_to_decide = []
for y in range(1, half+1):
    squares_to_decide += list([(x,y) for x in range(y)])

m = len(squares_to_decide)
ans = 1e9
for i in range(1<<m):
    included = set()
    included.add((0,0))
    for j in range(m):
        if (i&(1<<j)):
            included.add(squares_to_decide[j])
    
    p = get_solution(included)
    if (valid_solution(p)):
        
        pixels_changed = 0
        for i in range(n):
            for j in range(n):
                if p[i][j] != pattern[i][j]:
                    pixels_changed += 1
        ans = min(ans, pixels_changed)

print(ans)
