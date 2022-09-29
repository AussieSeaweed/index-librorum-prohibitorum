import sys
raw_input = sys.stdin.readline

for x in xrange(input()):
    nums = map(lambda _: int(_), raw_input().split())
    if nums[0] * nums[1] != nums[2]:
        print "16 BIT S/W ONLY"
    else:
        print "POSSIBLE DOUBLE SIGMA"