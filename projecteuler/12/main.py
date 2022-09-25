from math import sqrt



def divisors_of(value):
    divisors = set()

    for i in range(1, int(sqrt(value)) + 1):
        if value % i == 0:
            divisors.add(i)
            divisors.add(value // i)

    return divisors


def main():
    value = 0
    i = 0

    while len(divisors_of(value)) <= 500:
        value += i
        i += 1

    print(value)


if __name__ == '__main__':
    main()

