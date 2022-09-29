import sys
raw_input = sys.stdin.readline

string = raw_input()
max_length = 0

for i in xrange(len(string)+1):
    for j in xrange(i):
        if string[j:i] == string[j:i][::-1]:
            max_length = max(max_length, i - j)

print max_length