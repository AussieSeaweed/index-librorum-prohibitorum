from math import inf


def is_palindrome(value):
    return str(value) == ''.join(reversed(str(value)))


def main():
    value = -inf

    for i in range(100, 1000):
        for j in range(i, 1000):
            product = i * j

            if is_palindrome(product):
                value = max(value, product)

    print(value)


if __name__ == '__main__':
    main()

