r, c = map(int, input().split())
tb, lr, ud = (1, 6), (4, 3), (5, 2)
sum_ = 0


def left(n):
    global lr, tb

    if n == 0:
        return 0
    elif n >= 4:
        return n // 4 * (sum(lr) + sum(tb)) + left(n % 4)
    else:
        top = tb[0]
        lr, tb = tb, lr[::-1]

        return top + left(n - 1)


def right(n):
    global lr, tb

    if n == 0:
        return 0
    elif n >= 4:
        return n // 4 * (sum(lr) + sum(tb)) + right(n % 4)
    else:
        top = tb[0]
        lr, tb = tb[::-1], lr

        return top + right(n - 1)


def down():
    global tb, ud
    top = tb[0]
    tb, ud = ud, tb[::-1]

    return top


for i in range(r):
    direction = left if i & 1 else right
    sum_ += direction(c - 1) + down()

print(sum_)