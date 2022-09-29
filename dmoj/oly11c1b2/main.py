def convert(digits, base):
    return sum(digit * base ** i for i, digit in enumerate(digits))


def explore(s, base):
    digits = tuple(map(int, s))[::-1]
    values = set()

    for i in range(len(digits)):
        for digit in range(base):
            if digit != digits[i]:
                values.add(convert(digits[:i] + (digit,) + digits[i + 1:], base))

    return values


base2 = input()
base3 = input()

print((explore(base2, 2) & explore(base3, 3)).pop())