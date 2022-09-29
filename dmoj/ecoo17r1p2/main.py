class Candy:
    def __init__(self, name):
        self.name = name
        self.P = 0
        self.F = 0
        self.G = 0

    @property
    def total(self):
        return self.P + self.F + self.G

    @property
    def points(self):
        return self.G, self.F, self.P

    def __lt__(self, other):
        if self.total == other.total:
            return self.points < other.points
        else:
            return self.total < other.total

    def __eq__(self, other):
        return self.points == other.points


def maxima(values):
    max_value = max(values)

    for value in values:
        if value == max_value:
            yield value


for _ in range(10):
    N = int(input())
    candies = []
    candy = None

    while True:
        line = input()

        if line == '*':
            if candy:
                candies.append(candy)

            break
        elif line[0] == 'J':
            P, F, G = map(int, line.split()[1:])

            candy.P += P
            candy.F += F
            candy.G += G
        else:
            if candy:
                candies.append(candy)

            candy = Candy(line)

    print(','.join(candy.name for candy in maxima(candies)))