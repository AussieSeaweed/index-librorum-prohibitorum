import sys
input = sys.stdin.readline
sys.setrecursionlimit(1000000000)

MOD = 1 << 32


def factorial(n):
    if n > 33:
        return 0
    ret = 1

    for i in range(1, n + 1):
        ret = ret * i % MOD

    return ret


def main():
    N = int(input())
    for i in range(N):
        n = int(input())
        print(factorial(n))


if __name__ == "__main__":
    main()