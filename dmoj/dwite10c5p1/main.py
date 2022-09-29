for _ in range(5):
    W, C = input().split()
    L = set(input().split('+'))

    print(''.join('_' if c in L else w for w, c in zip(W, C)))