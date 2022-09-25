def is_palindromic(s):
    return s == s[::-1]


def main():
    value = 0

    for i in range(1000000):
        decimal_repr = str(i)
        binary_repr = bin(i)[2:]

        if is_palindromic(decimal_repr) and is_palindromic(binary_repr):
            value += i

    print(value)


if __name__ == '__main__':
    main()

