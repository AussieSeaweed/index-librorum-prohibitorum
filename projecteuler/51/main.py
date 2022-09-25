from itertools import count, product
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

    value = None

    for n in count(1):
        for chars in product('0123456789*', repeat=n):
            s = ''.join(chars)
            values = set(map(int, map(partial(s.replace, '*'), map(str, range(10)))))
            prime_family = set(filter(partial(getitem, sieve), values))

            if len(prime_family) == 8:
                value = min(prime_family)
                break
        
        if value is not None:
            break
    
    print(value)


if __name__ == '__main__':
    main()
