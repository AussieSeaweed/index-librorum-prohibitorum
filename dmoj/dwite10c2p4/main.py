def to_rec_dec(n, d):
    left = n // d
    n %= d

    rights = []
    indices = {}

    while n and n not in indices:
        indices[n] = len(rights)
        n *= 10
        rights.append(n // d)
        n %= d
    else:
        if n:
            non_repeats = ''.join(map(str, rights[:indices[n]]))
            repeats = ''.join(map(str, rights[indices[n]:]))
            right = f'{non_repeats}({repeats})'
        else:
            right = ''.join(map(str, rights))

    return f'{left}.{right}'


for _ in range(5):
    print(to_rec_dec(*map(int, input().split())))