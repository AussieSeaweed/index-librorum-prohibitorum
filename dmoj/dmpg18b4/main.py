from math import inf
from statistics import mean

N, M, X = map(int, input().split())

numerators = list(map(int, input().split()))
denominators = list(map(int, input().split()))

numerator_mean = mean(numerators)
numerator_min = min(numerators)
numerator_max = max(numerators)

optimizer = None
difference = inf

for denominator in sorted(denominators):
    if abs(numerator_mean / denominator - X / 100) < difference \
            and numerator_max <= denominator <= 2 * numerator_mean:
        optimizer = denominator
        difference = abs(numerator_mean / denominator - X / 100)

print(optimizer if optimizer is not None else 'Shimnanigans have failed')