def solve(E):
    min_, max_ = 1, len(E)

    while min_ != max_:
        i = (len(E) - 1) // 2
        e = E.pop(i)

        if e == min_:
            min_ = min_ + 1
        elif e == max_:
            max_ = max_ - 1
        else:
            return False

    return True


T = int(input())

for t in range(1, T + 1):
    N = int(input())
    E = list(map(int, input().split()))

    print(f'Case #{t}:', 'YES' if solve(E) else 'NO')