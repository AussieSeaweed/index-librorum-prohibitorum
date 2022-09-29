import sys
raw_input = sys.stdin.readline

date = [1989, 2, 27]
N = int(raw_input())

for x in range(N):
    nd = list(map(int, raw_input().split()))
    
    if nd <= date:
        print("Yes")
    else:
        print("No")