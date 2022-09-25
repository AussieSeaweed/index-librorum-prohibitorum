def main():
    d = 3
    value = 1

    while d <= 1001:
        for i in range(4):
            value += d * d - i * (d - 1)

        d += 2

    print(value)


if __name__ == '__main__':
    main()

