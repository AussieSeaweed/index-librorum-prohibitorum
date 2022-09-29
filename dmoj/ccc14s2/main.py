import sys
raw_input = sys.stdin.readline

raw_input()

r1 = raw_input().split()
r2 = raw_input().split()

for i, person in enumerate(r1):
    if not (person != r2[i] and person == r2[r1.index(r2[i])]):
        print "bad"
        break
else:
    print "good"