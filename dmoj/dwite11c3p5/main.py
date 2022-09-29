from itertools import product

for _ in range(5):
    results = []

    for _ in range(3):
        formulae = input()
        symbols = tuple(set(map(chr, range(ord('a'), ord('j') + 1))) & set(formulae))
        formulae = formulae.replace('v', 'or').replace('^', 'and').replace('~', 'not ')
        result = True

        for propositions in product(range(2), repeat=len(symbols)):
            for symbol, proposition in zip(symbols, propositions):
                globals()[symbol] = proposition

            result &= eval(formulae)

            if not result:
                break

        results.append(result)

    print(''.join(map(('N', 'Y').__getitem__, results)))