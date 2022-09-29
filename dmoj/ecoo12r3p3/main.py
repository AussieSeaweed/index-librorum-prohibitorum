from operator import add, sub, mul, mod

arithmetic = {
    '+': add,
    '-': sub,
    '*': mul,
    'q': lambda x, y: abs(x) // abs(y) * (x // abs(x) if x else 0) * y // abs(y),
    'r': mod,
}


def evaluate(expression):
    expression = expression.replace('(', '( ').replace(')', ' )')
    tokens = expression.split()

    while len(tokens) > 1:
        for i, (a, b, c) in enumerate(zip(tokens, tokens[1:], tokens[2:])):
            if a in arithmetic and b not in ('(', ')') and c not in ('(', ')'):
                tokens[i:i + 3] = [str(arithmetic[a](int(b), int(c)))]
                break
            elif a == '(' and b not in ('(', ')') and c == ')':
                tokens[i:i + 3] = [b]
                break

    return int(tokens[0])


for _ in range(10):
    print(evaluate(input().strip()))