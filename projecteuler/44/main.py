from math import isqrt


def get_pentagon(n):
    return n * (3 * n - 1) // 2


def is_pentagon(value):
    radicand = 1 + 24 * value
    root = isqrt(radicand)
    numerator = 1 + root
    denominator = 6

    return root ** 2 == radicand and numerator % denominator == 0


def main():
    value = None
    i = 1

    while value is None:
        p_i = get_pentagon(i)
        j = i - 1

        while value is None and j > 0: 
            p_j = get_pentagon(j)

            if is_pentagon(p_i + p_j) and is_pentagon(p_i - p_j):
                value = p_i - p_j
 
            j -= 1

        i += 1

    print(value)


if __name__ == '__main__':
    main()
