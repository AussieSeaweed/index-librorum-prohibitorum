def main():
    units = 1, 2, 5, 10, 20, 50, 100, 200
    counts = [0] * 201
    counts[0] = 1

    for unit in units:
        for i in reversed(range(len(counts))):
            for j in range(i + unit, len(counts), unit):
                counts[j] += counts[i]

    value = counts[-1]

    print(value)


if __name__ == '__main__':
    main()

