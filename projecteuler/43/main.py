from itertools import permutations


def solve(state):
    primes = 2, 3, 5, 7, 11, 13, 17
    pool = set(map(str, range(10))) - set(state)
    value = 0

    if len(state) == 0:
        for c in pool:
            value += solve(c)
    elif len(state) == 1:
        for permutation in permutations(pool, 3):
            s = ''.join(permutation)

            if int(s) % 2 == 0:
                value += solve(state + s)
    elif len(state) < 10:
        for c in pool:
            if int(state[-2:] + c) % primes[len(state) - 3] == 0:
                value += solve(state + c)
    else:
        value = int(state)

    return value


def main():
    value = solve('')

    print(value)


if __name__ == '__main__':
    main()

