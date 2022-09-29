A = 1
B = 1

N = int(input())

while A <= N:
    output = []
    
    if A % 7 == 0 and A % 13 == 0:
        output.append("Fizz Fuzz")
    elif A % 7 == 0:
        output.append("Fizz")
    elif A % 13 == 0:
        output.append("Fuzz")
    else:
        output.append(str(A))
        
    if B % 7 == 0 and B % 13 == 0:
        output.append("Fizz Fuzz")
    elif B % 7 == 0:
        output.append("Fizz")
    elif B % 13 == 0:
        output.append("Fuzz")
    else:
        output.append(str(B))
        
    print(" ".join(output))
        
    A += 1; B += 2