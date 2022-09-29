raw_input = __import__("sys").stdin.readline

alpha = "abcdefghijklmnopqrstuvwxyz"
ualpha = alpha.upper()
shift = -int(raw_input())

ui = list(raw_input())

for i in range(len(ui)):
    if ui[i].isalpha():
        if ui[i].isupper():
            ui[i] = ualpha[(ualpha.index(ui[i]) + shift) % 26]
        else:
            ui[i] = alpha[(alpha.index(ui[i]) + shift) % 26]

print("".join(ui))