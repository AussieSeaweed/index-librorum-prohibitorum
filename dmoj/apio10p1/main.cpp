#include <iostream>
#include <deque>
using namespace std;

int N, a, b, c;
long long dp[1000001], x[1000001];
deque<long long> M;
deque<long long> B;

void insert(long long m, long long b) {
    while (M.size() >= 2 && (b - B[B.size() - 2]) * (M[M.size() - 2] - M.back()) < (B.back() - B[B.size() - 2]) * (M[M.size() - 2] - m)) {
        M.pop_back();
        B.pop_back();
    }
    M.push_back(m);
    B.push_back(b);
}

long long query(long long x) {
    while (M.size() >= 2 && M.front() * x + B.front() < M[1] * x + B[1]) {
        M.pop_front();
        B.pop_front();
    }
    return M.front() * x + B.front();
}

int main() {
    scanf("%d%d%d%d", &N, &a, &b, &c);

    for (int i = 1; i <= N; i++) {
        scanf("%lld", x + i);
        x[i] += x[i - 1];
    }

    insert(0, 0);

    for (int n = 1; n <= N; n++) {
        dp[n] = a * x[n] * x[n] + b * x[n] + c + query(x[n]);
        insert(-2 * a  * x[n], dp[n] + a * x[n] * x[n] - b * x[n]);
    }

    printf("%lld", dp[N]);

    return 0;
}