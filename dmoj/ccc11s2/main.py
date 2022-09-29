import sys
raw_input = sys.stdin.readline
num = input()
teacher = [None for x in xrange(num)]
for x in xrange(num):
    teacher[x] = raw_input()
correct = 0
for x in xrange(num):
    student = raw_input()
    if student == teacher[x]:
        correct += 1
print correct