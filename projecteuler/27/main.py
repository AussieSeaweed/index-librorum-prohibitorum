from math import sqrt, inf, prod


def is_prime(value):
    if value < 2:
        return False

    for i in range(2, int(sqrt(value)) + 1):
        if value % i == 0:
            return False
    
    return True


def count(a, b):
    n = 0

    while is_prime(n ** 2 + a * n + b):
        n += 1

    return n


def main():
    max_n = -inf
    arguments = None

    for a in range(-1000, 1001):
        for b in range(-1000, 1001):
            n = count(a, b)

            if n > max_n:
                max_n = n
                arguments = a, b

    value = prod(arguments)
    
    print(value)


if __name__ == '__main__':
    main()

