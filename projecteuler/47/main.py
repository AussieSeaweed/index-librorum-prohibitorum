from functools import partial
from operator import getitem
from itertools import count


def sieve_until(n):
    sieve = [True] * (n + 1)
    sieve[0] = sieve[1] = False

    for i in range(2, n + 1):
        if not sieve[i]:
            continue

        for j in range(i * i, n + 1, i):
            sieve[j] = False
    
    return sieve


def primes_from(sieve):
    return tuple(filter(partial(getitem, sieve), range(len(sieve))))


def prime_factors_of(n, primes):
    factors = []

    while n != 1:
        for prime in primes:
            if n % prime == 0:
                factors.append(prime)
                n //= prime
                break
    
    return factors


def main():
    sieve = sieve_until(1000000)
    primes = primes_from(sieve)
    value = None
    
    for i in count(1):
        for j in range(i, i + 4):
            if len(set(prime_factors_of(j, primes))) != 4:
                break
        else:
            value = i
            break
    
    print(value)


if __name__ == '__main__':
    main()
