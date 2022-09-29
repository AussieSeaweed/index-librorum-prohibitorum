from collections import defaultdict
raw_input = __import__("sys").stdin.readline

graph = defaultdict(list)

N = input()

for i in xrange(N):
    x, y = map(int, raw_input().split())
    graph[x].append(y)
    

a, b = map(int, raw_input().split())

queue = [a]
visited = []

while queue:
    node = queue.pop(0)
    
    if node == b:
        print "Tangled"
        break
    
    for adj_node in graph[node]:
        if adj_node not in visited:
            queue.append(adj_node)
            visited.append(adj_node)
else:
    print "Not Tangled"