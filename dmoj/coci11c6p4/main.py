k = int(input())

n = 0
c = 1

while c < k:
    n += 1
    c += n

print(n)

for i in range(n):
    print(5000 - i - 1, -5000, -5000, -5000 + i + 1)