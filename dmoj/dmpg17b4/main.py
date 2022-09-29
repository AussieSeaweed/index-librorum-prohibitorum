from sys import setrecursionlimit

setrecursionlimit(10 ** 9)


def solve(lo, hi):
    if lo == hi:
        return []

    sub_solution = solve(lo + 1, hi)
    sub_solution.insert((hi - lo) // 2, lo)

    return sub_solution


print('\n'.join(map(str, solve(0, 1024))))