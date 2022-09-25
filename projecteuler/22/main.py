def alphabetical_value_of(name):
    return sum(ord(c) - ord('A') + 1 for c in name)


def main():
    with open('p022_names.txt') as file:
        names = [name.strip('"') for name in file.read().split(',')]

    names.sort()

    value = 0

    for i, name in enumerate(names):
        value += (i + 1) * alphabetical_value_of(name)

    print(value)


if __name__ == '__main__':
    main()

