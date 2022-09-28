#include <iostream>
#include <deque>
using namespace std;

int N;
unsigned long long a[100000], b[100000], dp[100000];
deque<unsigned long long> M;
deque<unsigned long long> B;

void insert(unsigned long long m, unsigned long long b) {
    while (M.size() >= 2 && (b - B[B.size() - 2]) / (double) (M[M.size() - 2] - m) <
                                (B.back() - B[B.size() - 2]) / (double) (M[M.size() - 2] - M.back())) {
        M.pop_back();
        B.pop_back();
    }
    M.push_back(m);
    B.push_back(b);
}

unsigned long long query(unsigned long long x) {
    while (M.size() >= 2 && M.front() * x + B.front() > M[1] * x + B[1]) {
        M.pop_front();
        B.pop_front();
    }
    return M.front() * x + B.front();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> N;

    for (int i = 0; i < N; i++) {
        cin >> a[i];
    }

    for (int i = 0; i < N; i++) {
        cin >> b[i];
    }

    dp[0] = 0;
    insert(b[0], dp[0]);

    for (int i = 1; i < N; i++) {
        dp[i] = query(a[i]);
        insert(b[i], dp[i]);
    }

    cout << dp[N - 1] << '\n';

    return 0;
}
