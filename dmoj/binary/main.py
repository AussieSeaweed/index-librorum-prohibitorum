for i in range(int(input())): print((lambda s: "".join([(" " if i % 4 == 0 else "") + s[i] for i in range(len(s))]))((lambda s: "0" * ((4 - len(s) % 4) % 4) + s)(bin(int(input()))[2:]))[1:])