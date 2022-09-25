from math import prod
from fractions import Fraction
from itertools import product


def main():
    fractions = set()

    for a, b, c, d in product(range(1, 10), repeat=4):
        if a == 0 or c == 0 or a > c or (a == c and b >= d):
            continue

        numerator = a, b
        denominator = c, d
        fraction = Fraction(a * 10 + b, c * 10 + d)

        for i in range(2):
            for j in range(2):
                if numerator[i] == denominator[j] and denominator[not j] != 0 and Fraction(numerator[not i], denominator[not j]) == fraction:
                    fractions.add(fraction)
    
    fraction = prod(fractions)
    value = fraction.denominator

    print(value)


if __name__ == '__main__':
    main()

