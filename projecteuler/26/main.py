from math import inf


def reciprocate(denominator):
    digits = []
    numerator = 1
    indices = {numerator: len(digits)}

    while numerator:
        digits.append(numerator // denominator)
        numerator %= denominator
        numerator *= 10
        
        if numerator in indices:
            return digits, len(digits) - indices[numerator]

        indices[numerator] = len(digits)

    return digits, 0 


def main():
    maximum = -inf
    maximand = None

    for d in range(1, 1000):
        _, value = reciprocate(d)

        if value > maximum:
            maximum = value
            maximand = d

    print(maximand)


if __name__ == '__main__':
    main()

