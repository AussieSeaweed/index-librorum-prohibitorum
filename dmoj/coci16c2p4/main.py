def generate_sequence(start, count, step=1):
    subsequence = range(start, start + (count - 1) * step, step)

    return tuple(subsequence) + ((start + (count - 2) * step) * count - sum(subsequence),)


n = int(input())

if n == 1:
    print(1)
elif n == 2:
    print(-1)
else:
    for start in generate_sequence(1, n, n ** 2):
        print(' '.join(map(str, generate_sequence(start, n))))