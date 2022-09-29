a = sorted([int(x) for x in input().split()])
b = sorted([int(x) for x in input().split()])
count = 0
for i in range(len(a)):
    if a[i] <= b[i]:
        count += 1

if count == 3:
    print ("Y")

else:
    print ("N")