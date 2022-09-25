from functools import partial


def count_days(year, month):
    leap = year % 4 == 0 and (year % 100 != 0 or year % 400 == 0)

    if month == 2:
        day_count = 29 if leap else 28
    elif month in {4, 6, 9, 11}:
        day_count = 30
    else:
        day_count = 31

    return day_count


def main():
    day_count = sum(map(partial(count_days, 1900), range(1, 13)))
    sunday_count = 0

    for year in range(1901, 2001):
        for month in range(1, 13):
            sunday_count += day_count % 7 == 6
            day_count += count_days(year, month)

    print(sunday_count)


if __name__ == '__main__':
    main()

