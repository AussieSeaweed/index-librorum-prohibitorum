def main():
    value = 0

    for i in range(1, 1001):
        value += i ** i

    print(str(value)[-10:])


if __name__ == '__main__':
    main()
