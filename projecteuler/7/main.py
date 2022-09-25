from itertools import count
from math import sqrt


def is_prime(value):
    if value < 2:
        return False

    for i in range(2, int(sqrt(value)) + 1):
        if value % i == 0:
            return False
    
    return True


def main():
    counter = count()
    primes = set()

    while len(primes) < 10001:
        value = next(counter)

        if is_prime(value):
            primes.add(value)

    print(max(primes))


if __name__ == '__main__':
    main()

