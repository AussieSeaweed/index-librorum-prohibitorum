import sys
raw_import = sys.stdin.readline

s = 0

for i in xrange(6):
    s += int(raw_input())
    
s /= 6.

AIF = int(raw_input())

if s + AIF >= int(raw_input()):
    print("yes")
else:
    print("no")