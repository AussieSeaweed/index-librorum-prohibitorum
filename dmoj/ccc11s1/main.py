import sys
raw_input = sys.stdin.readline

string = ""
for x in xrange(input()):
    string += raw_input()

Ts = string.count("t") + string.count("T")
Ss = string.count("s") + string.count("S")

if Ts > Ss:
    print "English"
else:
    print "French"