input = __import__("sys").stdin.readline # Fast input for python. Ignore

I = int(input())
N = int(input())
J = int(input())

difference_array = [0] * (I)

for _ in range(J):
    i, f, k = map(int, input().split())  # It's just getting the values
    i -= 1
    f -= 1
    difference_array[i] += k
    if f + 1 < I:
        difference_array[f + 1] -= k

ans = difference_array[0] < N

"""
If difference_array[0] < N
this is an equivalent of ans = True, which is numerically 1
otherwise, it is an equivalent of ans = False, which is numerically 0
"""

for i in range(1, I):
    difference_array[i] += difference_array[i - 1]
    ans += difference_array[i] < N

print(int(ans))  # I may be 1 and hence ans may store a boolean value