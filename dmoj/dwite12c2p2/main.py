def wtoi(word):
    value = 0

    for c in word:
        value = 26 * value + ord(c) - ord('A')

    return value


def itow(value):
    chars = []

    while value:
        chars.append(chr(value % 26 + ord('A')))
        value //= 26

    word = ''.join(reversed(chars))

    return word if word else 'A'


for _ in range(5):
    print(itow(sum(map(wtoi, input().split()))))