nums = []
for x in xrange(input()):
    num = input()
    if num:
        nums.append(num)
    else:
        nums.pop()

print(sum(nums))