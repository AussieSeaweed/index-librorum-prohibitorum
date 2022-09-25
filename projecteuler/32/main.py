from itertools import permutations


def main():
    products = set()

    for permutation in permutations(range(1, 10)):
        for i in range(1, len(permutation)):
            for j in range(i + 1, len(permutation)):
                s = ''.join(map(str, permutation))
                multiplier = int(s[:i])
                multiplicand = int(s[i:j])
                product = int(s[j:])
                
                if multiplier * multiplicand == product:
                    products.add(product)

    value = sum(products)

    print(value)


if __name__ == '__main__':
    main()

