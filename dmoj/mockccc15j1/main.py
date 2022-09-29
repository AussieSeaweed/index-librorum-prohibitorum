n = input().split()
nums = ["416", "647", "437"]
if (n[0] in nums) and (len(n[1]) == 7):
    if n[0] == nums[0]:
        print("valuable")
    else:
        print("valueless")
else:
    print("invalid")