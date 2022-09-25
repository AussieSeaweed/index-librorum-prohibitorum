from functools import partial
from operator import contains


def word_value_of(word):
    return sum(ord(c) - ord('A') + 1 for c in word)


def main():
    with open('p042_words.txt') as file:
        words = eval(file.read())

    word_values = list(map(word_value_of, words))
    max_word_value = max(word_values)
    triangle_numbers = [0]

    while triangle_numbers[-1] < max_word_value:
        n = len(triangle_numbers)

        triangle_numbers.append(n * (n + 1) // 2)

    triangle_numbers = set(triangle_numbers)

    count = sum(map(partial(contains, triangle_numbers), word_values))

    print(count)


if __name__ == '__main__':
    main()

