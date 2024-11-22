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
stdsteppath = os.path.join(probpath, 'psj', 'std_step.cpp')
chkpath = os.path.join(datapath, 'chk.cpp')

with open(os.path.join(probpath, 'conf.yaml'), mode='r', encoding='UTF-8') as f:
    file = yaml.safe_load(f)

np.random.seed(9300588)
random.seed(9300588)
MAXN = file['args']['n']
id = 0

def printcase(data: list):
    global id
    id += 1
    path = os.path.join(datapath, str(id))
    with open(path + ".in", 'w') as f:
        f.write(str(len(data)) + "\n")
        random.shuffle(data)
        for clist in data:
            f.write(str(len(clist)) + "\n")
            for p, x in enumerate(clist):
                f.write(str(x) + (" " if p != len(clist) - 1 else "\n"))
    os.system(f"std_step.exe < {path}.in > {path}.ans")
    print(f"data {id} complete.")

    os.system(f"std.exe < {path}.in > tmp")
    if os.system(f"chk.exe {path}.in tmp {path}.ans") != 0:
        os.remove("tmp")
        print("std wrong answer!")
        exit(0)
    os.remove("tmp")

# Compile
os.system(f"g++ -o std_step {stdsteppath} -O2 -DRUNGEN")
os.system(f"g++ -o std {stdpath} -O2 -DRUNGEN")
os.system(f"g++ -o chk {chkpath} -O2 -DRUNGEN")

# Data Func
def coin_flip(prob):
    return random.random() < prob
def randarray(n: int, sum: int, initial:int = 1):
    arr = [initial] * n
    for _ in range(sum - n * initial):
        arr[random.randint(0, n - 1)] += 1
    return arr

def randperm(n: int):
    numlist = list(range(1, n+1))
    random.shuffle(numlist)
    return numlist

def all2cyc(n: int):
    numlist = list(range(1, n+1))
    index = 0
    while index + 1 < len(numlist):
        if coin_flip(1 / n):
            index += 1
        else:
            numlist[index], numlist[index + 1] = numlist[index + 1], numlist[index]
            index += 2
    return numlist

def allsmallcyc(n: int):
    numlist = list(range(1, n+1))
    index = 0
    while index + 1 < len(numlist):
        if coin_flip(1 / n):
            index += 1
        else:
            l = random.randint(2, min(5, len(numlist) - index))
            rot = random.choice([1, -1])
            cur = numlist[index: index + l]
            numlist[index: index + l] = cur[rot:] + cur[:rot]
            index += l
    return numlist

def allcyc(n: int):
    numlist = list(range(1, n+1))
    rot = random.choice([1, -1])
    return numlist[rot:] + numlist[:rot]

def allcyc_randomrot(n: int):
    numlist = list(range(1, n+1))
    rot = random.randint(0, n - 1)
    return numlist[rot:] + numlist[:rot]

def complex(n: int):
    numlist = list(range(n+1))
    
    numcyc = random.randint(2, int(2 * math.sqrt(n)))
    elemcyc = random.randint(n // 10 * 9, n - 1)
    largecyclen = random.randint(1, elemcyc - numcyc)
    nums = randarray(numcyc - 1, elemcyc - largecyclen) + [largecyclen]
    random.shuffle(nums)
    gaps = randarray(numcyc + 1, n - elemcyc, initial=0)

    elemgaps = list(range(1, 1 + gaps[0]))
    cur = 1 + gaps[0]

    for id in range(numcyc):
        curarr = numlist[cur: cur + nums[id]]
        rot = random.choice([-1, 1])
        numlist[cur: cur+nums[id]] = curarr[rot:] + curarr[:rot]
        cur += nums[id]
        elemgaps += list(range(cur, cur + gaps[id + 1]))
        cur += gaps[id + 1]

    numcyc_gap = random.randint(1, int(2 * math.sqrt(len(elemgaps))))
    elem_gap = randarray(numcyc_gap, len(elemgaps))
    random.shuffle(elemgaps)
    cur = 0
    for t in elem_gap:
        curarr = elemgaps[cur: cur+t]
        cur += t
        random.shuffle(curarr)
        for id in range(t - 1):
            numlist[curarr[id]] = curarr[id + 1]
        if len(curarr) != 0:
            numlist[curarr[-1]] = curarr[0]

    del numlist[0]
    return numlist

def randomswap_small(n: int):
    numlist = list(range(1, n+1))
    for _ in range(random.randint(1, 100)):
        index = random.randint(0, n-2)
        numlist[index], numlist[index + 1] = numlist[index + 1], numlist[index]
    return numlist

def randomswap_large(n: int):
    numlist = list(range(1, n+1))
    for _ in range(random.randint(1, 5 * n)):
        index = random.randint(0, n-2)
        numlist[index], numlist[index + 1] = numlist[index + 1], numlist[index]
    return numlist

funclist = [complex, randomswap_small, randomswap_large, randperm, randperm, all2cyc, allsmallcyc, allcyc, allcyc_randomrot]

# Gen Data
for func in funclist:
    for nlist in [[random.randint(MAXN - 3, MAXN)], randarray(random.randint(50, 200), MAXN)]:
        printcase([func(n) for n in nlist])

for nlist in [randarray(random.randint(5, 10), MAXN), randarray(random.randint(10, 30), MAXN), randarray(random.randint(30, 100), MAXN), randarray(random.randint(100, 400), MAXN), randarray(random.randint(400, 1200), MAXN)]:
    printcase([random.choice(funclist)(n) for n in nlist])

for x in range(1, 13):
    printcase([randperm(x) for _ in range(MAXN // x)])
