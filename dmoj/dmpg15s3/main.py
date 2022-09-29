numberOfflowers = int(input())
flowers = [int(x) for x in input().split()]
sum = 0
pairs = int(input())
delete = []
shifts = 0
sub = 0
decrease = 0
for i in range(pairs):
    decrease = [int(x) for x in input().split()]
    x = decrease[0]
    y = decrease[1]
    if flowers[x - 1] > y and flowers[x] < y:
        sub += (flowers[x])
    elif flowers[x - 1] < y and flowers[x] > y:
        sub += (flowers[x - 1])
    elif flowers[x - 1] > y and flowers[x] > y:
        sub += y
    else:
        sub += (min(flowers[x - 1], flowers[x]))
for i in flowers:
    sum += i

print (sum - sub)