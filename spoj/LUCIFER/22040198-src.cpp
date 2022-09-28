#include <iostream>
#include <cstring>
#include <unordered_map>

using namespace std;

bool prime[46];
int N, digits[10], p_limit = 45;
unordered_map<int, long long> dp[10][2];

void build_sieve() {
    fill(prime, prime + p_limit + 1, true);

    prime[0] = false;
    prime[1] = false;

    for (int i = 2; i <= p_limit; i++) {
        if (prime[i])
            for (int j = i * i; j <= p_limit; j += i)
                prime[j] = false;
    }
}

bool is_prime(int n) {
    return n >= 2 && prime[n];
}

void store(int n) {
    N = 0;

    do {
        digits[N++] = n % 10;
    } while (n /= 10);
}

long long solve(int i, bool limit, int val) {
    if (i == -1) return is_prime(val);
    if (dp[i][limit].count(val)) return dp[i][limit][val];
    dp[i][limit][val] = 0;

    int k = limit ? digits[i] : 9, sign = i & 1 ? 1 : -1;
    for (int j = 0; j <= k; j++)
        dp[i][limit][val] += solve(i - 1, j == digits[i] ? limit : false, val + sign * j);

    return dp[i][limit][val];
}

long long lucifer_count(int n) {
    for (int i = 0; i < 10; i++) {
        dp[i][0].clear();
        dp[i][1].clear();
    }

    store(n);
    return solve(N - 1, true, 0);
}

int main() {
    build_sieve();
    int _;
    scanf("%d", &_);

    while (_--) {
        int A, B;
        scanf("%d%d", &B, &A);
        printf("%lld\n", lucifer_count(A) - lucifer_count(B - 1));
    }

    return 0;
}