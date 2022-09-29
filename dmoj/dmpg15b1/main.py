a = int(input())

for i in range(a):
    enter = input()
    if len(enter) == 10 and (enter[:3] == "416" or enter[:3] == "647"):
        print("(" + enter[:3] + ")-" + enter[3:6] + "-" + enter[6:])
    else:
        print("not a phone number")