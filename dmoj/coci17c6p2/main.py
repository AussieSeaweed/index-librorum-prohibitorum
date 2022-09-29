from collections import defaultdict

n, m = map(int, input().split())
A = set(map(int, input().split()))
k = int(input())
L = []
products = []
reactions = defaultdict(list)

for i in range(k):
    l, _ = map(int, input().split())
    L.append(l)

    for x in map(int, input().split()):
        reactions[x].append(i)

    products.append(tuple(map(int, input().split())))

B = set()

while A:
    a = A.pop()
    B.add(a)

    for i in reactions[a]:
        L[i] -= 1

        if not L[i]:
            for product in products[i]:
                if product not in B:
                    A.add(product)

print(len(B))
print(' '.join(map(str, sorted(B))))