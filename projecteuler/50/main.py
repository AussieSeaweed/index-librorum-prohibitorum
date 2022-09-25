from functools import partial
from operator import getitem


def sieve_until(n):
    sieve = [True] * n
    sieve[0] = sieve[1] = False

    for i in range(n):
        if not sieve[i]:
            continue

        for j in range(i * i, n, i):
            sieve[j] = False
    
    return sieve


def main():
    sieve = sieve_until(1000000)
    primes = tuple(filter(partial(getitem, sieve), range(len(sieve))))
    value = None
    count = 0

    for i in range(len(primes)):
        sum_ = 0

        for j in range(i, len(primes)):
            sum_ += primes[j]

            if sum_ >= len(sieve):
                break
            elif sieve[sum_] and j - i + 1 >= count:
                value = sum_
                count = j - i + 1
 
    print(value)


if __name__ == '__main__':
    main()
