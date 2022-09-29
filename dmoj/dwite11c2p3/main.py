from collections import defaultdict

for _ in range(5):
    N, M = map(int, input().split())
    store_records = [input().split() for _ in range(N)]
    student_records = [input().split() for _ in range(M)]

    preferences = defaultdict(set)

    for store_id, info, product in store_records:
        preferences[info].add(product)

    count = 0

    for name, info in student_records:
        if len(preferences[info]) == 1:
            count += 1

    print(count)