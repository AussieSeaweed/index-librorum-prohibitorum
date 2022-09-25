from math import inf


def triangular(n):
    return n * (n + 1) // 2


def pentagonal(n):
    return n * (3 * n - 1) // 2


def hexagonal(n):
    return n * (2 * n - 1)


def main():
    value = -inf
    indices = [0, 0, 0]

    while value <= 40755:
        values = triangular(indices[0]), pentagonal(indices[1]), hexagonal(indices[2])
        
        if len(set(values)) == 1:
            value = values[0]
        
        i = values.index(min(values))
        indices[i] += 1
    
    print(value)


if __name__ == '__main__':
    main()
