def main():
    value = 0

    for i in range(1000):
        if i % 3 == 0 or i % 5 == 0:
            value += i
    
    print(value)


if __name__ == '__main__':
    main()

