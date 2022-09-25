from math import factorial


def main():
    result = factorial(100)
    digits = list(map(int, str(result)))
    value = sum(digits)

    print(value)


if __name__ == '__main__':
    main()

