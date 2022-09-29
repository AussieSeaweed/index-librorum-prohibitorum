import sys
from collections import defaultdict
raw_input = sys.stdin.readline

count = 0
depth = 0

def traverse(n):
    global count
    for node in graph[n]:
        traverse(node)
        count += 2
    

def max_depth(n, d):
    global depth
    if d > depth:
        depth = d
    for node in graph[n]:
        max_depth(node, d + 2)


for x in range(int(raw_input())):
    graph = defaultdict(set)
    N = int(raw_input())
    ui = [None] * N
    visited = set()
    
    for y in range(N):
        ui[y] = raw_input().rstrip()
        
    prev = None
    for y in reversed(ui):
        if prev is None:
            visited.add(y)
        if y not in visited:
            visited.add(y)
            graph[prev].add(y)

        prev = y
    
    traverse(ui[-1])
    max_depth(ui[-1], 0)
    
    print((count - depth) * 10)
    
    count = 0
    depth = 0