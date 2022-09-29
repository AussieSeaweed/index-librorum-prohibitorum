from sys import stdin


def solve(K):
    dp = [(0, 0)]

    for k in K:
        if k < dp[-1][0]:
            dp.append(dp[-1])
        elif k > dp[-1][0]:
            dp.append((k, 1))
        else:
            dp.append((k, dp[-1][1] + 1))

    return dp


def main():
    n, q = map(int, stdin.readline().split())
    K = tuple(map(int, stdin.readline().split()))
    dp1 = solve(K)
    dp2 = solve(reversed(K))

    for _ in range(q):
        a, b = map(int, stdin.readline().split())

        if dp1[a - 1][0] == dp2[n - b][0]:
            print(dp1[a - 1][0], dp1[a - 1][1] + dp2[n - b][1])
        else:
            print(' '.join(map(str, max(dp1[a - 1], dp2[n - b]))))


if __name__ == '__main__':
    main()