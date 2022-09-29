raw_input = __import__("sys").stdin.readline

sq = int(raw_input())

r = int(raw_input())
c = int(raw_input())

mat = [list(raw_input().rstrip()) for x in xrange(r)]


def find(matrix, row, col, rn, cn, ID):
    if 0 <= row and row < rn and 0 <= col and col < cn and mat[row][col] == 0:
        matrix[row][col] = ID
        find(matrix, row-1, col, rn, cn, ID)
        find(matrix, row+1, col, rn, cn, ID)
        find(matrix, row, col-1, rn, cn, ID)
        find(matrix, row, col+1, rn, cn, ID)


for row in xrange(r):
    for col in xrange(c):
        if mat[row][col] == ".":
            mat[row][col] = 0
        else:
            mat[row][col] = -1

ID = 1
for row in xrange(r):
    for col in xrange(c):
        if mat[row][col] == 0:
            find(mat, row, col, r, c, ID)
            ID += 1

rooms = [0] * ID
for row in xrange(r):
    for col in xrange(c):
        if mat[row][col] > 0:
            rooms[mat[row][col]] += 1

floored = 0
while sq > 0:
    most = 0
    for x in xrange(len(rooms)):
        if rooms[x] > rooms[most]:
            most = x

    if most == 0:
        break
    else:
        if rooms[most] <= sq:
            sq -= rooms[most]
            rooms[most] = -1
            floored += 1
        else:
            break

room = " room, " if floored == 1 else " rooms, "
print str(floored) + room + str(sq) + " square metre(s) left over"