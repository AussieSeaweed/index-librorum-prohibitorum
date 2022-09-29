from itertools import product
from math import lcm


def stoi(s):
    h, m = map(int, s.split(':'))
    return h * 60 + m


def itos(i):
    weekdays = ['Saturday', 'Sunday', 'Monday', 'Tuesday', 'Wednesday', 'Thursday', 'Friday']
    d, h, m = i // 60 // 24 % 7, i // 60 % 24, i % 60
    return f'{weekdays[d]}\n{h:02d}:{m:02d}'


a = stoi(input())
b = stoi(input())
da = stoi(input())
db = stoi(input())
na = lcm(da, db) // da + b // da
nb = lcm(da, db) // db + a // db

for ia, ib in product(range(na), range(nb)):
    if (i := a + ia * da) == b + ib * db:
        print(itos(i))
        break
else:
    print('Never')