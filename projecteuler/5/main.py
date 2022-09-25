from functools import reduce


def gcd(a, b):
    while b:
        a, b = b, a % b

    return a


def lcm(a, b):
    return a * b // gcd(a, b)


def main():
    value = reduce(lcm, range(1, 21))

    print(value)

    
if __name__ == '__main__':
    main()

