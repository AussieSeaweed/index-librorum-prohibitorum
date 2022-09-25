def main():
    value = 0

    for i in range(10 ** 6):
        s = str(i)
        digits = list(map(int, s))
        terms = [digit ** 5 for digit in digits]

        if i == sum(terms):
            value += i

    print(value - 1)


if __name__ == '__main__':
    main()
