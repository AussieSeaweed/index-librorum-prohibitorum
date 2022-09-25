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


def abundance_of(a):
    return d(a) > a


def main():
    abundant_values = set(filter(abundance_of, range(28124)))
    values = set()

    for i in range(28124):
        for abundant_value in abundant_values:
            delta = i - abundant_value

            if delta in abundant_values:
                values.add(i)
    value = 0

    for i in range(1, 28124):
        if i not in values:
            value += i

    print(value)


if __name__ == '__main__':
    main()

