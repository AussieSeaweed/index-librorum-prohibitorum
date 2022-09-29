alphabets = "abcdefghijklmnopqrstuvwxyz"

string = list(raw_input().rstrip())

i = len(string)-1

while 1:
    char = string[i][-1]
    if "a" <= char and char <= "m":
        string[i] = "a"
        break
    else:
        string[i] = "a"
        if i == 0:
            string.insert(0, "a")
            break
        elif string[i-1] == "z":
            pass
        else:
            string[i-1] = alphabets[alphabets.index(string[i-1])+1]
            break

    i -= 1


print "".join(string)