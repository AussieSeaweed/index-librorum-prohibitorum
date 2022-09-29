from collections import deque


class Edge:
    def __init__(self, u, v, capacity):
        self.u = u
        self.v = v
        self.capacity = capacity
        self.flow = 0

    def other(self, node):
        return self.v if self.u == node else self.u

    def get_residual_capacity_to(self, node):
        return self.capacity - self.flow if node == self.v else self.flow

    def add_flow_to(self, node, delta):
        if node == self.v:
            self.flow += delta
        else:
            self.flow -= delta


inf = 1000000000
e = [0 for _ in range(101)]
graph = [[] for _ in range(200)]
level = [inf for i in range(200)]
N = input()

for i in range(1, N):
    e[i] = input()
    edge = Edge(i, i + 100, e[i])
    graph[i].append(edge)
    graph[i + 100].append(edge)

M = input()

for _ in range(M):
    i, j = map(int, raw_input().split())
    edge = Edge(i + 100, j, inf)
    graph[i + 100].append(edge)
    graph[j].append(edge)


def bfs(source, sink):
    for i in range(N + 100):
        level[i] = inf

    level[source] = 0
    queue = deque([source])

    while len(queue) > 0:
        node = queue.popleft()

        for adj_edge in graph[node]:
            other = adj_edge.other(node)
            if level[other] == inf and adj_edge.get_residual_capacity_to(other) > 0:
                level[other] = level[node] + 1
                queue.append(other)

    return level[sink] != inf


def dfs(node, target, pushed):
    if node == target:
        return pushed

    left_over = pushed

    for adj_edge in graph[node]:
        other = adj_edge.other(node)
        if level[node] + 1 == level[other] and adj_edge.get_residual_capacity_to(other) > 0 and left_over > 0:
            sent = dfs(other, target, min(left_over, adj_edge.get_residual_capacity_to(other)))
            adj_edge.add_flow_to(other, sent)
            left_over -= sent

    return pushed - left_over


def dinic(source, sink):
    ret = 0

    while bfs(source, sink):
        ret += dfs(source, sink, inf)

    return ret


print(dinic(1, N))