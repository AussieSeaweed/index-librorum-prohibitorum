from sys import setrecursionlimit

setrecursionlimit(1000000)


def dfs(node):
    for neighbor in sames[node]:
        if values[neighbor] is None:
            values[neighbor] = values[node]

            if not dfs(neighbor):
                return False
        elif values[neighbor] != values[node]:
            return False

    for neighbor in diffs[node]:
        if values[neighbor] is None:
            values[neighbor] = not values[node]

            if not dfs(neighbor):
                return False
        elif values[neighbor] == values[node]:
            return False

    return True


n, m = map(int, input().split())
values = [None] * n
sames = [[] for _ in range(n)]
diffs = [[] for _ in range(n)]

for _ in range(m):
    tokens = input().split()
    preference, i, j = tokens[0], int(tokens[1]) - 1, int(tokens[2]) - 1
    graph = sames if preference == 'S' else diffs
    graph[i].append(j)
    graph[j].append(i)


runs = []

for i in range(n):
    if values[i] is None:
        values[i] = False
        runs.append(dfs(i))

if all(runs):
    print('1' + '0' * len(runs))
else:
    print(0)