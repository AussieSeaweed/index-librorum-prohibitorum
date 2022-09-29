def dfs(node, pred):
    r, c = node
    preds[r][c] = (None, None) if pred is None else pred

    for dr, dc in ((0, 1), (1, 0), (0, -1), (-1, 0)):
        if 0 <= r + dr < R and 0 <= c + dc < C and maze[r + dr][c + dc] != '#' \
                and preds[r + dr][c + dc] is None:
            dfs((r + dr, c + dc), (r, c))


R, C = int(input()), int(input())
V, H, E = None, None, None
maze = [input() for _ in range(R)]

for r in range(R):
    for c in range(C):
        if maze[r][c] == 'V':
            V = r, c
        elif maze[r][c] == 'H':
            H = r, c
        elif maze[r][c] == 'E':
            E = r, c

preds = [[None] * C for _ in range(R)]
dfs(E, None)

vpath = []
hpath = []

node = V
while node != (None, None):
    vpath.append(node)
    node = preds[node[0]][node[1]]

node = H
while node != (None, None):
    hpath.append(node)
    node = preds[node[0]][node[1]]

vpath = list(reversed(vpath))[:-1]
hpath = list(reversed(hpath))[:-1]

t = 0

while vpath and hpath:
    t += 1

    vnodes = vpath[-2:]
    del vpath[-2:]
    hnode = hpath.pop()

    if hnode in vnodes:
        print(t)
        break
else:
    if vpath:
        print('escape')
    else:
        print(t + len(hpath))