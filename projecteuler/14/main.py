memo = {}


def collatz_sequence_len_of(value):
    if value in memo:
        return memo[value]
    
    if value == 1:
        memo[value] = 0
    elif value % 2 == 0:
        memo[value] = 1 + collatz_sequence_len_of(value // 2)
    else:
        memo[value] = 1 + collatz_sequence_len_of(3 * value + 1)

    return memo[value]


def main():
    value = max(range(1, 1000000), key=collatz_sequence_len_of)

    print(value)


if __name__ == '__main__':
    main()

