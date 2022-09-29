import sys
raw_input = sys.stdin.readline

board = [[10**10]*8 for x in xrange(8)]


xi, yi = map(int, raw_input().split())
xf, yf = map(int, raw_input().split())

queue = [(xi-1, yi-1, 0)]
while queue:
  move = queue.pop()
  if move[0] >= 0 and move[0] < 8 and move[1] >= 0 and move[1] < 8 and board[move[0]][move[1]] > move[2]:
    board[move[0]][move[1]] = move[2]
    queue.insert(0,(move[0] - 1, move[1] + 2, move[2] + 1))
    queue.insert(0,(move[0] - 1, move[1] - 2, move[2] + 1))
    queue.insert(0,(move[0] + 1, move[1] + 2, move[2] + 1))
    queue.insert(0,(move[0] + 1, move[1] - 2, move[2] + 1))
    queue.insert(0,(move[0] - 2, move[1] + 1, move[2] + 1))
    queue.insert(0,(move[0] - 2, move[1] - 1, move[2] + 1))
    queue.insert(0,(move[0] + 2, move[1] + 1, move[2] + 1))
    queue.insert(0,(move[0] + 2, move[1] - 1, move[2] + 1))

print board[xf-1][yf-1]