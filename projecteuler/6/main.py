def square(value):
    return value ** 2


def main():
    values = range(1, 101)
    sum_of_squares = sum(map(square, values))
    square_of_sum = square(sum(values))
    difference = square_of_sum - sum_of_squares

    print(difference)


if __name__ == '__main__':
    main()

