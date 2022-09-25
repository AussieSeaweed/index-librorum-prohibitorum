from collections import Counter
from functools import partial
from operator import mul, eq


def main():
    value = None
    i = 1

    while value is None:
        digits = Counter(str(i))

        if all(map(partial(eq, digits), map(Counter, map(str, map(partial(mul, i), range(2, 7)))))):
            value = i
        
        i += 1

    print(value)


if __name__ == '__main__':
    main()
