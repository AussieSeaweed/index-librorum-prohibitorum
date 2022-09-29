def solve(n):
    bits = []

    while n:
        bits.append(n & 1)
        n >>= 1

    for i in range(len(bits) - 1):
        if bits[i] and not bits[i + 1]:
            bits[i] = 0
            bits[i + 1] = 1

            subbits = bits[:i]
            bits[:i] = [1] * subbits.count(1) + [0] * subbits.count(0)

            break
    else:
        bits[-1] = 0
        bits.append(1)

        subbits = bits[:-2]
        bits[:-2] = [1] * subbits.count(1) + [0] * subbits.count(0)

    res = 0

    for i in range(len(bits)):
        res += bits[i] * (1 << i)

    return res


for _ in range(5):
    print(solve(int(input())))