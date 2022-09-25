from math import comb


def main():
    count = 0

    for n in range(1, 101):
        for r in range(n + 1):
            count += comb(n, r) > 1000000
    
    print(count)


if __name__ == '__main__':
    main()
