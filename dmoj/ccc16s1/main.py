a = raw_input()
b = raw_input()

for i in "qwertyuiopasdfghjklzxcvbnm":
    if a.count(i) < b.count(i):
        print("N")
        break
else:
    print("A")