N = int(input())
M = int(input())
graph = [[] for i in range(N + 1)]
visited = [False for i in range(N + 1)]
in_path = [False for i in range(N + 1)]

for i in range(M):
    u, v = map(int, input().split())
    graph[u].append(v)


def dfs(node):
    visited[node] = True
    in_path[node] = True

    ret = False

    for adj in graph[node]:
        if in_path[adj]:
            ret = True
            break
        if not visited[adj]:
            ret = ret or dfs(adj)

    in_path[node] = False

    return ret

ans = False

for i in range(1, N + 1):
    if not visited[i]:
        ans = ans or dfs(i)

if ans:
    print("N")
else:
    print("Y")