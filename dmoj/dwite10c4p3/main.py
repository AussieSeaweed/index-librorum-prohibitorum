def get_next_bw(n):
    s = '0' + bin(n)[2:]
    index = -1

    for i in range(len(s) - 1, 0, -1):
        if s[i] == '1' and s[i - 1] == '0':
            front = s[:i - 1] + '1'
            rem_count = s.count('1') - front.count('1')
            back = '0' * (len(s) - len(front) - rem_count) + '1' * rem_count

            return int(front + back, 2)
    else:
        raise ValueError


for _ in range(5):
    N = int(input())
    print(get_next_bw(N))