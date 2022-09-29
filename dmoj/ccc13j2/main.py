rotatable = ["I", "O", "S", "H", "Z", "X", "N"]

for x in raw_input().rstrip():
    if x not in rotatable:
        print "NO"
        break
else:
    print "YES"