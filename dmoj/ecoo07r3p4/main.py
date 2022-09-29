from collections.abc import Callable
from operator import add, sub, mul, truediv


class Arithmetic:
    symbol: str
    op: Callable
    priority: int
    associative: bool

    def __init__(self, left_operand, right_operand):
        self.left_operand = left_operand
        self.right_operand = right_operand

    def __float__(self):
        return self.op(float(self.left_operand), float(self.right_operand))

    def __str__(self):
        if isinstance(self.left_operand, Arithmetic) \
                and self.left_operand.priority < self.priority:
            left_operand = f'({self.left_operand})'
        else:
            left_operand = self.left_operand
        if isinstance(self.right_operand, Arithmetic) \
                and (not self.associative if self.right_operand.priority == self.priority else self.right_operand.priority < self.priority):
            right_operand = f'({self.right_operand})'
        else:
            right_operand = str(self.right_operand)

        return f'{left_operand} {self.symbol} {right_operand}'


class Addition(Arithmetic):
    symbol = '+'
    op = add
    priority = 0
    associative = True


class Subtraction(Arithmetic):
    symbol = '-'
    op = sub
    priority = 0
    associative = False


class Multiplication(Arithmetic):
    symbol = '*'
    op = mul
    priority = 1
    associative = True


class Division(Arithmetic):
    symbol = '/'
    op = truediv
    priority = 1
    associative = False


class Exponentiation(Arithmetic):
    symbol = '!'
    op = pow
    priority = 2
    associative = False


arithmetic = {cls.symbol: cls for cls in Arithmetic.__subclasses__()}


for _ in range(5):
    expression = input()
    stack = []
    i = 0

    for j in range(len(expression)):
        if not expression[j].isdigit() and expression[j] != '.':
            if i < j:
                stack.append(expression[i:j])
            if expression[j] in arithmetic:
                stack.append(arithmetic[expression[j]](stack.pop(-2), stack.pop()))

            i = j + 1

    print(stack[-1], '=', float(stack[-1]))