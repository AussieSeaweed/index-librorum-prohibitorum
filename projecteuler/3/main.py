from math import sqrt, ceil


def main(): 
    value = 600851475143
    sieve = [1] * (ceil(sqrt(value)) + 1)
    sieve[0] = sieve[1] = 0
    max_factor = None

    for i in range(len(sieve)):
        if not sieve[i]:
            continue

        if value % i == 0:
            max_factor = i

        for j in range(i * i, len(sieve), i):
            sieve[j] = 0

    print(max_factor)


if __name__ == '__main__':
    main()
    
