from math import factorial

s = input()

for i in range(20, -1, -1):
    if str(i) + '!' in s:
        print(factorial(i))
        break
else:
    print(-1)