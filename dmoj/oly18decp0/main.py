lines = input().split(". ")
for i in range(len(lines)):
    if lines[i][0].isalpha():
        lines[i] = lines[i][0].upper() + lines[i][1:]
print(". ".join(lines))