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
    sieve = sieve_until(10000)
    primes = tuple(i for i in range(1000, 10000) if sieve[i])
    values = None

    for i in range(len(primes)):
        for j in range(i + 1, len(primes)):
            a = primes[i]
            b = primes[j]
            c = 2 * primes[j] - primes[i]
            
            if sorted(str(a)) == sorted(str(b)) == sorted(str(c)) and sieve[c] and a != 1487:
                values = a, b, c
                break
        
        if values is not None:
            break
    
    print(''.join(map(str, values)))


if __name__ == '__main__':
    main()
