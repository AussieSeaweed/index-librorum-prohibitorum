from collections import defaultdict

K, N = map(int, input().split())
words = [input() for _ in range(K)]
word_lists = defaultdict(list)

for word in words:
    word_lists[word[0]].append(word)

for value in word_lists.values():
    value.sort(reverse=True)

lookup = {key: value.copy() for key, value in word_lists.items()}

for _ in range(N):
    char = input()

    if not lookup[char]:
        lookup[char] = word_lists[char].copy()

    print(lookup[char].pop())