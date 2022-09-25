def main():
    counts = {
            1: 3,
            2: 3,
            3: 5,
            4: 4,
            5: 4,
            6: 3,
            7: 5,
            8: 5,
            9: 4,
            10: 3,
            11: 6,
            12: 6,
            13: 8,
            14: 8,
            15: 7,
            16: 7,
            17: 9,
            18: 8,
            19: 8,
            20: 6,
            30: 6,
            40: 5,
            50: 5,
            60: 5,
            70: 7,
            80: 6,
            90: 6,
    }
    
    for i in range(10, 100):
        if i not in counts:
            counts[i] = counts[i // 10 * 10] + counts[i % 10]

    for i in range(100, 1000):
        if i not in counts:
            counts[i] = counts[i // 100] + 7
            
            if i % 100:
                counts[i] += 3 + counts[i % 100]
                
    counts[1000] = 11

    value = sum(counts.values())

    print(value)


if __name__ == '__main__':
    main()

