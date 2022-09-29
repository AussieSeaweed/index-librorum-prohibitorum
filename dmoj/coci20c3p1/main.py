n = int(input())
d = list(map(int, input().split()))
moves = []

while d:
    d_min = min(d)
    index = d.index(d_min)

    for _ in range(index):
        moves.append('UZMI L L')
        moves.append('STAVI L D')

    moves.append('UZMI D L')

    for _ in range(index):
        moves.append('UZMI L D')
        moves.append('STAVI L L')

    moves.append('STAVI D D')

    d.remove(d_min)

for _ in range(n):
    moves.append('UZMI L D')
    moves.append('STAVI L L')

print(len(moves))
print('\n'.join(moves))