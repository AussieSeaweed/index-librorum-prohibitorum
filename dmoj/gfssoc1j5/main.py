from collections import defaultdict

input = __import__("sys").stdin.readline

N, M, T = map(int, input().split())

graph = defaultdict(list)

for i in range(M):
    a, b = map(int, input().split())
    graph[a].append(b)

Q = int(input())

INF = 9999999999999

dist = [[INF] * (N + 1) for _ in range(N + 1)]

for i in range(1, N + 1):
    q = [i]

    dist[i][i] = 0

    while q:
        node = q.pop(0)

        for adj in graph[node]:
            if dist[i][node] + T < dist[i][adj]:
                dist[i][adj] = dist[i][node] + T
                q.append(adj)

for q in range(Q):
    a, b = map(int, input().split())
    print("Not enough hallways!" if dist[a][b] == INF else dist[a][b])