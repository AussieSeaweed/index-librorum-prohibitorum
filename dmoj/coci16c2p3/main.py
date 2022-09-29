from collections import deque

n = int(input())
A = deque(map(int, input().split()))
count = 0

while len(A) > 1:
    if A[0] < A[-1]:
        A.appendleft(A.popleft() + A.popleft())
        count += 1
    elif A[0] > A[-1]:
        A.append(A.pop() + A.pop())
        count += 1
    else:
        A.popleft()
        A.pop()

print(count)