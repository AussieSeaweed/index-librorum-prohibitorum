for _ in range(5):
    pattern = input()
    count = 0

    for i in range(256):
        string = bin(i)[2:]
        string = '0' * (8 - len(string)) + string

        if pattern not in string:
            count += string.count('1')

    print(count)