from functools import partial
from operator import getitem


def sieve_until(n):
    sieve = [True] * n
    sieve[0] = sieve[1] = False

    for i in range(n):
        if not sieve[i]:
            continue

        for j in range(i * i, n, i):
            sieve[j] = False

    return sieve


def rotations_of(s):
    for i in range(len(s)):
        yield s[i:] + s[:i]


def main():
    sieve = sieve_until(1000000)
    count = 0

    for i in range(len(sieve)):
        if all(map(partial(getitem, sieve), map(int, rotations_of(str(i))))):
            count += 1

    print(count)


if __name__ == '__main__':
    main()

