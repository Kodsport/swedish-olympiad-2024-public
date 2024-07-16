#!/usr/bin/python3

n = int(input())
pattern = [[int(x) for x in input()] for i in range(n)]
half = n//2

def can_transform(x,y):
    return abs(x) <= half and abs(y) <= half

def transform_in_quadrant(x,y):
    if x >= 0 and y > 0:
        return x,y
    if x < 0 and y >= 0:
        return y,-x
    if x > 0 and y <= 0:
        return -y,x
    if x <= 0 and y < 0:
        return -x,-y
    return 0,0

def transform_in_triangle(x,y):
    x,y = transform_in_quadrant(x,y)
    if x>y:
        x,y = y,x
    return x,y

def get_neighbors(x, y):
    non_transformed = [(x+1,y),(x-1,y),(x,y+1),(x,y-1)]
    ret = []
    for (_x,_y) in non_transformed:
        if not can_transform(_x,_y):
            continue
        __x,__y = transform_in_triangle(_x,_y)
        ret.append((__x,__y))
    return ret

def get_squares(x, y):
    squares = []
    for dx in [-1,1]:
        for dy in [-1,1]:
            non_transformed = [(x,y),(x+dx,y),(x,y+dy),(x+dx,y+dy)]
            if not all([can_transform(_x,_y) for _x,_y in non_transformed]):
                continue
            squares.append([transform_in_triangle(_x,_y) for _x,_y in non_transformed])
    return squares

def de_transform(x,y):
    return [(x,y), (y,x), (x,-y), (y,-x), (-x,y), (-y,x), (-x,-y), (-y,-x)]

def copy(x):
    y = set()
    for i in x:
        y.add(i)
    return y

def upper_edge(x, y):
    return y == half

def generate(current, visited, disallowed):
    x,y = current
    if x == y and x != 0:
        return [], []
    
    visited.add(current)

    _visited = [copy(visited)]
    _disallowed = [copy(disallowed)]
    

    prev_nei = None

    for _x,_y in set(get_neighbors(x,y)):
        if upper_edge(_x, _y) and not upper_edge(x, y):
            continue

        if prev_nei is not None:
            for i in range(len(_visited)):
                _disallowed[i].add(prev_nei)

        _new_visited = []
        _new_disallowed = []

        for i in range(len(_visited)):
            vis = _visited[i]
            dis = _disallowed[i]

            if (_x,_y) in vis or (_x,_y) in dis:
                continue

            # Check for cycle
            nei_visited_count = 0
            for _ in get_neighbors(_x,_y):
                if _ in vis:
                    nei_visited_count += 1
            if nei_visited_count > 1:
                dis.add((_x,_y))
                continue

            _vis = copy(vis)
            _dis = copy(dis)

            new_vis, new_dis = generate((_x,_y), _vis, _dis)
            
            for j in range(len(new_vis)):
                _new_visited.append(new_vis[j])
                _new_disallowed.append(new_dis[j])
        prev_nei = (_x,_y)

        
        for nv in _new_visited:
            _visited.append(nv)
        for nd in _new_disallowed:
            _disallowed.append(nd)

    # check for crooks
    __visited = []
    __disallowed = []
    for i in range(len(_visited)):
        neis = []

        for _ in get_neighbors(x,y):
            if _ in _visited[i]:
                neis.append(_)
        if len(neis) != 2:
            __visited.append(_visited[i])
            __disallowed.append(_disallowed[i])
        else:
            x1,y1 = neis[0]
            x2,y2 = neis[1]
            if (x1+x2)==2*x and (y1+y2)==2*y:
                __visited.append(_visited[i])
                __disallowed.append(_disallowed[i])
    return __visited, __disallowed

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

all_visited, _ = generate((0,0), set(), set())

def diff(p1, p2):
    s = 0
    for i in range(n):
        for j in range(n):
            s += abs(p1[i][j] - p2[i][j])
    return s

ans = 1e9
for v in all_visited: 
    ans = min(ans, diff(get_solution(v), pattern))

print(ans)

