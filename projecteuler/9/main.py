def main():
    product = None

    for a in range(1, 1001):
        for b in range(a + 1, 1000 - a + 1):
            c = 1000 - a - b
            if a ** 2 + b ** 2 == c ** 2:
                product = a * b * c

    print(product)


if __name__ == '__main__':
    main()

