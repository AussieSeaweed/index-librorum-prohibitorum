from math import isqrt
from itertools import count


def is_prime(n):
    if n < 2:
        return False

    for i in range(2, isqrt(n) + 1):
        if n % i == 0:
            return False
    
    return True


def is_doubled_square(n):
    return n % 2 == 0 and isqrt(n // 2) ** 2 == n // 2


def main():
    value = None

    for i in count(3, 2):
        if is_prime(i):
            continue

        for j in range(i):
            if is_prime(j) and is_doubled_square(i - j):
                break
        else:
            value = i
            break
    
    print(value)


if __name__ == '__main__':
    main()
