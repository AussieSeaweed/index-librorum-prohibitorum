def count_triangles(perimeter):
    count = 0

    for a in range(perimeter + 1):
        for b in range(a, perimeter - a + 1):
            c = perimeter - a - b

            if a ** 2 + b ** 2 == c ** 2:
                count += 1

    return count


def main():
    value = max(range(1001), key=count_triangles)

    print(value)


if __name__ == '__main__':
    main()

