cards = (list(range(2, 11)) + [10] * 3 + [11]) * 4

N = int(input())
card_sum = 0

for _ in range(N):
    card = int(input())
    cards.remove(card)
    card_sum += card

ge_count = sum(card > 21 - card_sum for card in cards)
lt_count = sum(card <= 21 - card_sum for card in cards)

print('DOSTA' if ge_count >= lt_count else 'VUCI')