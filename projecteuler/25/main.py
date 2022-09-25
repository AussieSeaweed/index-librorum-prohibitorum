from math import log10


def main():
    a, b = 1, 1
    n = 2

    while log10(b) < 1000 - 1:
        a, b = b, a + b
        n += 1

    print(n)


if __name__ == '__main__':
    main()

