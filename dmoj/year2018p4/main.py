dp = [[[-1, -1] for j in range(163)] for i in range(19)]
digits = [0] * 19
N = 0


def solve(i, s, limit):
    if i == -1:
        return 1 if s == 0 else 0
    if s < 0:
        return 0
    if dp[i][s][limit] != -1:
        return dp[i][s][limit]
    dp[i][s][limit] = 0

    k = digits[i] if limit else 9

    for j in range(k + 1):
        dp[i][s][limit] += solve(i - 1, s - j, j == k and limit)

    return dp[i][s][limit]


def store(n):
    global N
    N = 0

    while n:
        digits[N] = n % 10
        N += 1
        n //= 10


def digit_dp(n, cnt):
    for i in range(19):
        for j in range(163):
            dp[i][j][0] = -1
            dp[i][j][1] = -1

    store(n)

    for i in range(163):
        cnt[i] = solve(N - 1, i, True)


def main():
    l, r = [0] * 163, [0] * 163
    L, R = map(int, input().split())
    digit_dp(L - 1, l)
    digit_dp(R, r)

    ans = 0

    for i in range(163):
        ans += r[i] - l[i] > 0

    print(ans)


if __name__ == "__main__":
    main()