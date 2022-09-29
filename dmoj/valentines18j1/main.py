N = int(input())
K = max(int(input()) / 1000 for _ in range(N))

if K > 10:
    print('Something is wrong with these cuteness values')
elif K > 1:
    print('Cuteness by definition is similarity to Cactus')
else:
    print('Cuteness by definition is similarity to Carol')