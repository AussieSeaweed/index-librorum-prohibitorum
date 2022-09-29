from collections import deque


def solve_aux(from_, to):
    while from_:
        if from_[0] == to[0] - 1:
            to.appendleft(from_.popleft())
        elif from_[-1] == to[0] - 1:
            to.appendleft(from_.pop())
        elif from_[0] == to[-1] + 1:
            to.append(from_.popleft())
        elif from_[-1] == to[-1] + 1:
            to.append(from_.pop())
        else:
            return False

    return True


def solve(values):
    return solve_aux(deque(values[1:]), deque([values[0]])) \
           or solve_aux(deque(values[:-1]), deque([values[-1]]))


T = int(input())

for t in range(1, T + 1):
    N = int(input())
    values = tuple(map(int, input().split()))

    print(f'Case #{t}:', 'yes' if solve(values) else 'no')