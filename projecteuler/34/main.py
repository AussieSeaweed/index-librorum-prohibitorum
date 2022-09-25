from math import factorial


def main():
    value = 0

    for i in range(1000000):
        digit_factorials = list(map(factorial, map(int, str(i))))

        if sum(digit_factorials) == i:
            value += i

    print(value - 3)


if __name__ == '__main__':
    main()

