from collections import defaultdict


def conv(x):
    t = x
    digit_sum = 0

    while t:
        digit_sum += t % 10
        t //= 10

    return x * digit_sum % 99999


dictionary = list(map(str, map(conv, range(50000))))

for _ in range(5):
    m = input()

    print(sum(word.startswith(m) for word in dictionary))