def main():
    digits = []
    i = 1

    while len(digits) < 1000000:
        digits.extend(map(int, str(i)))
        i += 1
    
    value = 1

    for i in range(7):
        value *= digits[10 ** i - 1]

    print(value)


if __name__ == '__main__':
    main()

