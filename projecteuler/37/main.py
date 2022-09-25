from math import sqrt
from collections import deque


def is_prime(value):
    if value < 2:
        return False

    for i in range(2, int(sqrt(value)) + 1):
        if value % i == 0:
            return False

    return True


def left_to_right_primes_from(state, limit=6, depth=0):
    if depth == limit or not is_prime(int(state)):
        return

    yield state

    for value in range(1, 10):
        neighbor = f'{value}{state}'

        yield from left_to_right_primes_from(neighbor, limit, depth + 1)


def right_to_left_primes_from(state, limit=6, depth=0):
    if depth == limit or not is_prime(int(state)):
        return

    yield state

    for value in range(1, 10):
        neighbor = f'{state}{value}'

        yield from right_to_left_primes_from(neighbor, limit, depth + 1)


def main():
    initial_states = '2', '3', '5', '7'
    left_to_right_primes = set()
    right_to_left_primes = set()

    for initial_state in initial_states:
        left_to_right_primes |= set(left_to_right_primes_from(initial_state))
        right_to_left_primes |= set(right_to_left_primes_from(initial_state))

    values = (left_to_right_primes & right_to_left_primes) - set(initial_states)

    print(sum(map(int, values)))

if __name__ == '__main__':
    main()

