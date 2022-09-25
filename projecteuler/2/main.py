def main():
    a = 0
    b = 1
    value = 0

    while b <= 4000000:
        if b % 2 == 0:
            value += b

        a, b = b, a + b

    print(value)


if __name__ == '__main__':
    main()

