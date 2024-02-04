import random

class permutation:
    def __init__(self, p):
        self.p = p
        n = len(p)
        self.cycles = []
        self.which_cycle = [-1]*n
        self.index = [-1]*n
        marked = set()
        for i in range(n):
            if i not in marked:
                cyc = []
                j = i
                while j not in marked:
                    marked.add(j)
                    self.index[j] = len(cyc)
                    cyc.append(j)
                    self.which_cycle[j] = len(self.cycles)
                    j = self.p[j]
                self.cycles.append(cyc)
        
    
    def step(self, i, steps):
        length = len(self.cycles[self.which_cycle[i]])

        return self.cycles[self.which_cycle[i]][(length + self.index[i] + steps)%length]

    def exponentiate(self, x):
        p2 = []
        for i in range(len(self.p)):
            p2.append(self.step(i, x))
        new_permutation = permutation(p2)
        return new_permutation

def get_permutation(m, cycles):
    p1 = list(range(m))
    random.shuffle(p1)
    p2 = [0]*m
    starts = random.sample(range(1,m), cycles-1)
    starts.append(0)
    starts.sort()

    for i in range(len(starts)):
        j = m
        if i+1 < len(starts):
            j = starts[i+1]
        for i2 in range(starts[i], j):
            if i2 < j-1:
                p2[p1[i2]] = p1[i2+1]
            else:
                p2[p1[i2]] = p1[starts[i]]
    
    perm = permutation(p2)
    return perm

def equal_cycles(length, cycles):
    m = length*cycles
    p1 = list(range(m))
    random.shuffle(p1)
    p2 = [0]*m
    for i in range(cycles):
        start = i*length
        for j in range(length):
            a = start+j
            b = start+(j+1)%length
            p2[p1[a]] = p1[b]
    perm = permutation(p2)
    return perm

