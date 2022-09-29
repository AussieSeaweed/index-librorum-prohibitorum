digit_count = int(input())
digits = list(input())

for i in range(digit_count - 1):
    if ord(digits[i]) < ord(digits[i + 1]):
        digits[i], digits[i + 1] = digits[i + 1], digits[i]
        break

print(''.join(digits))