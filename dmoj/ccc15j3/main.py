ui = raw_input()

v = "aeiou"
c = "bcdfghjklmnpqrstvwxyzz"
find = {
    "a":"bc",
    "e":"dfg",
    "i":"hjkl",
    "o":"mnpqr",
    "u":"stvwxyz"
}

output = ""

for i in ui:
    output += i
    if i in c:
        for _v, _c in find.items():
            if i in _c:
                output += _v

        output += c[c.index(i)+1]

print(output)