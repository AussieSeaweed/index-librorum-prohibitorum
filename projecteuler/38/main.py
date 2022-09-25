from collections import Counter
from math import inf


def solve(value):
    i = 0
    digits = []

    while len(digits) < 9:
        i += 1 
        digits.extend(str(i * value))

    return int(''.join(digits)) if Counter(digits) == Counter(map(str, range(1, 10))) else -inf


def main():
    value = max(map(solve, range(10000)))

    print(value)


if __name__ == '__main__':
    main()

