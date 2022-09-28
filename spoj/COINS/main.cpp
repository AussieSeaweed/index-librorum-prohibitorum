#include <iostream>
#include <unordered_map>
using namespace std;

unordered_map<long long, long long> dp;

long long solve(long long N) {
    if (N == 0) return 0;
    if (dp.count(N)) return dp[N];

    return dp[N] = max(N, solve(N / 2) + solve(N / 3) + solve(N / 4));
}

int main() {
    long long N;
    while (cin >> N) {
        printf("%lld\n", solve(N));
    }

    return 0;
}