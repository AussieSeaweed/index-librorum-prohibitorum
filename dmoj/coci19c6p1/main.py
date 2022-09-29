from bisect import bisect_right


class Date:
    def __init__(self, day, month, year):
        self.day = day
        self.month = month
        self.year = year

    def __lt__(self, other):
        return self.data[::-1] < other.data[::-1]

    def __str__(self):
        return f'{self.day:02}.{self.month:02}.{self.year:04}.'

    @classmethod
    def get_day_count(cls, month, year):
        if month == 2:
            return 28 + (year % 4 == 0)
        elif 1 <= month <= 7:
            return 30 + (month & 1)
        else:
            return 31 - (month & 1)

    @property
    def data(self):
        return self.day, self.month, self.year

    @classmethod
    def is_valid(cls, day, month, year):
        return 1 <= day <= cls.get_day_count(month, year) and 1 <= month <= 12

    @classmethod
    def parse(cls, string):
        return Date(*map(int, string.split('.')[:-1]))


palindromic_dates = []

for year in range(10000):
    day = int(''.join(reversed(f'{year % 100:02}')))
    month = int(''.join(reversed(f'{year // 100:02}')))

    if Date.is_valid(day, month, year):
        palindromic_dates.append(Date(day, month, year))

N = int(input())

for _ in range(N):
    print(palindromic_dates[bisect_right(palindromic_dates, Date.parse(input()))])