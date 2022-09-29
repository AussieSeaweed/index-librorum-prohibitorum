N = int(input())
state = input()
skip = '0'
count = 0

for char in reversed(state):
    if char != skip:
        skip = char
        count += 1

print(count)