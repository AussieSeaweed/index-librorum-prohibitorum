from itertools import permutations
from math import sqrt, inf


def is_prime(value):
    if value < 2:
        return False

    for i in range(2, int(sqrt(value)) + 1):
        if value % i == 0:
            return False

    return True


def main():
    max_value = -inf

    for i in range(9):
        for permutation in permutations(range(1, i + 2)):
            value = int(''.join(map(str, permutation)))

            if is_prime(value) and value > max_value:
                max_value = value

    print(max_value)


if __name__ == '__main__':
    main()

