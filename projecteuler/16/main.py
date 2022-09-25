def main():
    digits = list(map(int, str(1 << 1000)))
    value = sum(digits)

    print(value)


if __name__ == '__main__':
    main()

