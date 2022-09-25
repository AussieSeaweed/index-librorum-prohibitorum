from math import sqrt


def divisors_of(value):
    divisors = set()

    for i in range(1, int(sqrt(value)) + 1):
        if value % i == 0:
            divisors.add(i)
            divisors.add(value // i)

    return divisors


def proper_divisors_of(value):
    divisors = divisors_of(value)
    divisors.discard(value)

    return divisors


def d(value):
    return sum(proper_divisors_of(value))


def amicability_of(a):
    b = d(a)

    return a != b and d(b) == a


def main():
    amicables = filter(amicability_of, range(1, 10000))
    value = sum(amicables)

    print(value)


if __name__ == '__main__':
    main()

