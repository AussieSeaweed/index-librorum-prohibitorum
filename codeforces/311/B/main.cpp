#include <iostream>
#include <algorithm>
#include <deque>

#define inf 9000000000000000000

long long dp[2][100001], d[100001], t[100001], l[100001], s[100001], N, M, P;
std::pair<long long, long long> cats[100001];
std::deque<long long> m, b;

void insert(long long slope, long long yint) {
    while (m.size() >= 2 && (yint - b[b.size() - 2]) / (double) (m[m.size() - 2] - slope) <=
                            (b.back() - b[b.size() - 2]) / (double) (m[m.size() - 2] - m.back())) {
        m.pop_back();
        b.pop_back();
    }
    m.push_back(slope);
    b.push_back(yint);
}

long long query(long long x) {
    while (m.size() >= 2 && m.front() * x + b.front() > m[1] * x + b[1]) {
        m.pop_front();
        b.pop_front();
    }
    return m.front() * x + b.front();
}

int main() {
    scanf("%lld%lld%lld", &N, &M, &P);

    for (int i = 2; i <= N; i++) {
        scanf("%lld", d + i);
        d[i] += d[i - 1];
    }

    for (int i = 1; i <= M; i++) {
        scanf("%lld%lld", &cats[i].second, &cats[i].first);
        cats[i].first -= d[cats[i].second];
    }

    std::sort(cats + 1, cats + M + 1);

    for (int i = 1; i <= M; i++) {
        t[i] = cats[i].first + d[cats[i].second];
        t[i] += t[i - 1];
        s[i] = cats[i].first;
        l[i] = d[cats[i].second];
        l[i] += l[i - 1];
    }

    std::fill(dp[0], dp[0] + M + 1, inf);
    dp[0][0] = 0;

    for (int p = 1, h = 1, ph = 0; p <= P; p++, h = !h, ph = !ph) {
        m.clear();
        b.clear();
        insert(0, 0);
        for (int i = 1; i <= M; i++) {
            dp[h][i] = -t[i] + s[i] * i + l[i] + query(s[i]);
            insert(-i, dp[ph][i] + t[i] - l[i]);
        }
    }

    printf("%lld\n", dp[P & 1][M]);

    return 0;
}
