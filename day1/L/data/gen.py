import yaml
import os
import sys
import random
import math
import numpy as np
import itertools

datapath = os.path.dirname(__file__)
probpath = os.path.dirname(datapath)
downpath = os.path.join(probpath, "down")
stdpath = os.path.join(probpath, 'psj', 'std.cpp')

with open(os.path.join(probpath, 'conf.yaml'), mode='r', encoding='UTF-8') as f:
    file = yaml.safe_load(f)

np.random.seed(9300588)
random.seed(9300588)
MAXN = file['args']['n']
ID = 0

def printcase(n: int, plist: list, edgelist: list):
    global ID
    ID += 1
    path = os.path.join(datapath, str(ID))
    with open(path + ".in", 'w') as f:
        f.write(str(n) + " " + str(len(edgelist)) + " " + str(len(plist)) + "\n")
        for id, p in enumerate(plist):
            f.write(str(p) + (" " if id != len(plist) - 1 else "\n"))
        random.shuffle(edgelist)
        for x, y, r in edgelist:
            f.write(str(x) + " " + str(y) + " " + str(r) + "\n")
    if os.system(f"std.exe < {path}.in > {path}.ans") != 0:
        exit()
    print(f"data {ID} complete.")

# Compile
os.system(f"g++ -o std {stdpath} -O2 -DRUNGEN")

# Data Func
def coin_flip(prob):
    return random.random() < prob

def total_random(n: int, m: int, c: int):
    plist = random.choices(range(1, n+1), weights = [random.randint(1, n)] + [random.randint(1, 5) for _ in range(n - 2)] + [random.randint(1, n)], k = c)
    containlist = [[] for _ in range(n + 1)]
    for i in range(c):
        containlist[plist[i]].append(i + 1)
    edgelist = []
    for _ in range(m):
        x, y = random.randint(1, n), random.randint(1, n)
        while len(containlist[x]) == 0:
            x = random.randint(1, n)
        r = random.choice(containlist[x])
        if coin_flip(0.5):
            x, y = y, x
        edgelist.append((x,y,r))
    printcase(n, plist, edgelist)

def largeans(n: int, m: int, c: int):
    plist = [random.choice([1, n]) for _ in range(c)]
    edgelist = [(1, n, random.choice(range(1, c+1))) for _ in range(m)]
    printcase(n, plist, edgelist)

def mistakelarge(n: int, m: int, c: int):
    plist = [1, 2, n] + random.choices(range(1, n + 1), k = c - 3)
    pointuse = random.randint(1, min(m // 2, n - 3))
    edgelist = []
    for p in range(3, 3 + pointuse):
        if p % 2:
            edgelist.append((1, p, 1))
            edgelist.append((p, 2, 2))
        else:
            edgelist.append((2, p, 2))
            edgelist.append((p, n, 3))
    leftp = []
    leftpoint = [1] + list(range(3 + pointuse, n + 1))
    for i, x in enumerate(plist):
        if x <= 1 or x >= 3 + pointuse:
            leftp.append(i)
    leftid = random.choices(leftp, k = m - len(edgelist))
    leftnewp = random.choices(leftpoint, k = m - len(edgelist))
    for i in range(m - len(edgelist)):
        x, y, r = plist[leftid[i]], leftnewp[i], leftid[i] + 1
        if coin_flip(0.5):
            x, y = y, x
        edgelist.append((x, y, r))
    printcase(n, plist, edgelist)

def bipartite_random_nocluster(n: int, m: int, c: int, w: int):
    c = m
    plist = []
    edgelist = []
    def addedge(x: int, y: int):
        edgelist.append((x, y, len(plist) + 1))
        plist.append(random.choice([x, y]))
    llist, rlist = []
    for x in range(2, n):
        if coin_flip(0.5):
            llist.append(x)
        else:
            rlist.append(x)
    for edgetype in random.choices(range(3), weights = [1,1,w], k = m):
        if edgetype == 0:
            addedge(1, random.choice(llist))
        elif edgetype == 1:
            addedge(random.choice(rlist), n)
        else:
            addedge(random.choice(llist), random.choice(rlist))
    printcase(n, plist, edgelist)

def bipartite_cyc_nocluster(n: int, m: int, c: int):
    c = m
    n = m // 2
    if n % 2:
        n -= 1
    plist = []
    edgelist = []
    def addedge(x: int, y: int):
        edgelist.append((x, y, len(plist) + 1))
        plist.append(random.choice([x, y]))
    llist, rlist = list(range(2, n // 2 + 1)), list(range(n // 2 + 1, n))
    random.shuffle(llist)
    random.shuffle(rlist)
    for (x, y) in zip(llist, rlist):
        addedge(1, x)
        addedge(x, y)
        addedge(y, n)
    llist = llist[-1:] + llist[:-1]
    for (x, y) in zip(llist, rlist):
        addedge(x, y)
    printcase(n, plist, edgelist)

def bipartite_random_nocluster(n: int, m: int, c: int, w: int):
    c = m
    plist = []
    edgelist = []
    def addedge(x: int, y: int):
        edgelist.append((x, y, len(plist) + 1))
        plist.append(random.choice([x, y]))
    llist, rlist = [], []
    for x in range(2, n):
        (llist if coin_flip(0.5) else rlist).append(x)
    for edgetype in random.choices(range(3), weights = [1,1,w], k = m):
        if edgetype == 0:
            addedge(1, random.choice(llist))
        elif edgetype == 1:
            addedge(random.choice(rlist), n)
        else:
            addedge(random.choice(llist), random.choice(rlist))
    printcase(n, plist, edgelist)

def bipartite_random(n: int, m: int, c: int, w: int):
    plist = random.choices(range(1, n+1), weights = [random.randint(1, n)] + [random.randint(1, 5) for _ in range(n - 2)] + [random.randint(1, n)], k = c)
    containlist = [[] for _ in range(n + 1)]
    for i in range(c):
        containlist[plist[i]].append(i + 1)
    llist, rlist = [], []
    for x in range(2, n):
        (llist if coin_flip(0.5) else rlist).append(x)
    edgelist = []
    for edgetype in random.choices(range(3), weights = [1,1,w], k = m):
        if edgetype == 0:
            x, y = 1, random.choice(llist)
            r = random.choice(containlist[1 if len(containlist[y]) == 0 or coin_flip(0.5) else y])
        elif edgetype == 1:
            x, y = random.choice(rlist), n
            r = random.choice(containlist[n if len(containlist[x]) == 0 or coin_flip(0.5) else x])
        else:
            leftorright = random.randint(0, 1)
            x, y = random.choice(llist), random.choice(rlist)
            while len(containlist[x if leftorright else y]) == 0:
                x, y = random.choice(llist), random.choice(rlist)
            r = random.choice(containlist[x if leftorright else y])
        edgelist.append((x, y, r))
    printcase(n, plist, edgelist)

# Gen Data
funclist_with_w = [(lambda n, m, c: func(n, m, c, w)) for func in [bipartite_random_nocluster, bipartite_random] for w in [0.5, 1.5, 2.5]]
funclist = [total_random, largeans, mistakelarge, bipartite_cyc_nocluster] + funclist_with_w

for n in [1000, 10000, MAXN]:
    for c in [1000, 10000, MAXN]:
        for _ in range(5):
            func = random.choice(funclist)
            print(func)
            func(n - random.randint(0, 10), MAXN - random.randint(0, 50), c - random.randint(0, 10))
