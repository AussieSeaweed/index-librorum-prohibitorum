bob, n = map(int, input().split())

bank = []
for i in range(n):
  userinput = int(input())
  bank.append(userinput)
  
bank = sorted(bank)

x = sum(bank) + bob
average = x/(len(bank) + 1)
count = 0
answer = 0

for i in range(len(bank) - 1, 0, -1):
  x -= bank[i]
  del bank[i]
  new = (x)/(len(bank) + 1)
  count += 1
  if new < average:
    average = new 
    answer = count
print (answer)