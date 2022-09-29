N = int(input())
line = [input() for _ in range(N)]
S = []

while line:
    if line < line[::-1]:
        S.append(line.pop(0))
    else:
        S.append(line.pop())

print(''.join(S))