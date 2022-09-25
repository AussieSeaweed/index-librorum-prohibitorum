def main():
    sieve = [1] * 2000001
    sieve[0] = sieve[1] = 0

    for i in range(len(sieve)):
        if not sieve[i]:
            continue

        for j in range(i * i, len(sieve), i):
            sieve[j] = 0

    value = 0

    for i in range(len(sieve)):
        if sieve[i]:
            value += i

    print(value)


if __name__ == '__main__':
    main()

