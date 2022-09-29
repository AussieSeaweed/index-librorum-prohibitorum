import sys
raw_input = sys.stdin.readline

N = int(raw_input())
name = raw_input()

substr = set()

for i in range(0, len(name)):
    substr.add(name[:i])

for i in range(N):
    numerator = ""
    denominator = ""
    current_name = ""

    ui = raw_input().rstrip()

    slash = False
    space = False
    for i in ui:
        if i == "/":
            slash = True
            continue
        elif i == " ":
            space = True
            slash = False
            continue

        if slash:
            denominator += i
        elif space:
            current_name += i
        else:
            numerator += i



    if numerator == "" or denominator == "":
        print("Y")
    elif current_name == "":
        numerator = int(numerator)
        denominator = int(denominator)

        if numerator / denominator > 1:
            print("Y")
        else:
            print("N")
    else:
        numerator = int(numerator)
        denominator = int(denominator)

        if numerator / denominator > 1 and current_name in substr:
            print("Y")
        else:
            print("N")