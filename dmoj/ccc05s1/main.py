import sys
raw_input = sys.stdin.readline

for x in xrange(int(raw_input())):
    num = list(raw_input().rstrip())
    while "-" in num:
        num.remove("-")
    num = num[:10]
    for y in xrange(len(num)):
        if num[y].isalpha():
            num[y] = num[y].lower()
            if num[y] in "abc":
                num[y] = "2"
            elif num[y] in "def":
                num[y] = "3"
            elif num[y] in "ghi":
                num[y] = "4"
            elif num[y] in "jkl":
                num[y] = "5"
            elif num[y] in "mno":
                num[y] = "6"
            elif num[y] in "pqrs":
                num[y] = "7"
            elif num[y] in "tuv":
                num[y] = "8"
            elif num[y] in "wxyz":
                num[y] = "9"

    num.insert(3, "-")
    num.insert(7, "-")
    print "".join(num)