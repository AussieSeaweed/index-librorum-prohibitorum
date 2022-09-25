def permutations_of(values):
    if not values:
        yield ()

    for i in range(len(values)):
        sub_values = values[:i] + values[i + 1:]

        for sub_permutation in permutations_of(sub_values):
            yield (values[i],) + sub_permutation
        

def main():
    values = tuple(range(10))

    for i, permutation in enumerate(permutations_of(values)):
        if i + 1 == 1000000:
            values = permutation
            break

    print(''.join(map(str, values)))


if __name__ == '__main__':
    main()

