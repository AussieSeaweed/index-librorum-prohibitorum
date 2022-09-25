memo = {}


def count_paths(r, c):
    if (r, c) in memo:
        return memo[r, c]

    if not r and not c:
        memo[r, c] = 1
    elif not r:
        memo[r, c] = count_paths(r, c - 1)
    elif not c:
        memo[r, c] = count_paths(r - 1, c)
    else:
        memo[r, c] = count_paths(r, c - 1) + count_paths(r - 1, c)

    return memo[r, c]


def main():
    print(count_paths(20, 20))


if __name__ == '__main__':
    main()

