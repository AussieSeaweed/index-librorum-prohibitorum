count_edible = 0

W, H = map(int, input().split())

bush = list()

for _ in range(H):
    bush.append(input())

for i in range(len(bush)):
    count_edible += bush[i].count("o")
    bush[i] = bush[i].replace("o", " ").replace("*", " ")

for line in bush:
    print(line)

print("o" * count_edible)