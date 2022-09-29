S = input()
T = input()
N = 0

for s, t in zip(S, T):
    if s != t:
        break

    N += 1

print(len(S) + len(T) - 2 * N)