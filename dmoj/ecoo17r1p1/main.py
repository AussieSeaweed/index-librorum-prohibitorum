for _ in range(10):
    trip_cost = int(input())
    percentages = list(map(float, input().split()))
    student_count = int(input())
    student_counts = [int(percentage * student_count) for percentage in percentages]
    student_counts[percentages.index(max(percentages))] += student_count - sum(student_counts)

    revenue = student_counts[0] * 12 + student_counts[1] * 10 + student_counts[2] * 7 + student_counts[3] * 5

    print('YES' if revenue / 2 < trip_cost else 'NO')