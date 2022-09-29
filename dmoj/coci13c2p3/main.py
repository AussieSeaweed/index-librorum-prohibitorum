from itertools import count, chain


def rev(word):
    partitions = [[], []]

    for i in range(len(word)):
        partitions[i & 1].append(word[i])

    return ''.join(chain(partitions[0], reversed(partitions[1])))


X = int(input())
word = input()
N = None

temp = word

for i in count(1):
    temp = rev(temp)

    if temp == word:
        N = i
        break

for _ in range(X % N):
    word = rev(word)

print(word)