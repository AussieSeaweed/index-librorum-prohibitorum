import sys, collections
raw_input = sys.stdin.readline

weight = int(raw_input())
bridge = collections.deque()
count = 0


for x in range(int(raw_input())):
    bridge.appendleft(int(raw_input()))
    if len(bridge) > 4:
        bridge.pop()
    if sum(bridge) <= weight:
        count += 1
    else:
        break

print(count)