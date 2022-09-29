for _ in range(5):
    N = int(input())
    costumes = set()
    names = []

    for _ in range(N):
        name, costume = input().split()

        if costume in costumes:
            names.append(name)

        costumes.add(costume)

    if names:
        print(' '.join(names))
    else:
        print('SPOOKY')