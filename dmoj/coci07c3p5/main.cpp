#include <bits/stdc++.h>
#include <bits/extc++.h>
#define scan(x) do{while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0');}while(0)
char _;
template<typename T>constexpr const T&_min(const T&x,const T&y) {return x<y?x:y;}
template<typename T>constexpr const T&_max(const T&x,const T&y) {return x<y?y:x;}
template<typename T,typename...Ts> constexpr const T&_min(const T&x,const Ts&...xs) {return _min(x,_min(xs...));}
template<typename T,typename...Ts> constexpr const T&_max(const T&x,const Ts&...xs) {return _max(x,_max(xs...));}
#define min(...) _min(__VA_ARGS__)
#define max(...) _max(__VA_ARGS__)
#define INF 9000000000000000000
#define inf 2000000000
using namespace std;

int S, A[17], B[17];
long long dp[17][2][136], dp2[17][2][2][136];
bool visited[17][2][2][136], possible[17][2][2][136];

long long solve(int index, bool tight, int sum, int digits[]) {
    if (index == -1)
        return sum == 0;
    if (~dp[index][tight][sum]) return dp[index][tight][sum];

    dp[index][tight][sum] = 0;
    int lim = min(sum, tight ? digits[index] : 9);
    for (int i = 0; i <= lim; i++)
        dp[index][tight][sum] += solve(index - 1, i == lim && tight, sum - i, digits);

    return dp[index][tight][sum];
}

long long solve(int digits[]) {
    memset(dp, -1, sizeof dp);
    return solve(16, true, S, digits);
}

void store(long long num, int digits[]) {
    int i = 0;
    while (num) {
        digits[i++] = num % 10;
        num /= 10;
    }
}

bool is_possible(int index, bool tightleft, bool tightright, int s) {
    if (visited[index][tightleft][tightright][s]) return dp2[index][tightleft][tightright][s];
    visited[index][tightleft][tightright][s] = true;

    int tmp = index;
    long long base = 1;

    while (tmp--)
        base *= 10;

    if (index == 0) {
        int begin = tightleft ? A[index] : 0, end = tightright ? B[index] : 9;
        for (int i = begin; i <= end; i++) {
            if (i == s) {
                dp2[index][tightleft][tightright][s] = i;
                return possible[index][tightleft][tightright][s] = true;
            }
        }
        return possible[index][tightleft][tightright][s] = false;
    } else {
        int begin = tightleft ? A[index] : 0, end = tightright ? B[index] : 9;
        for (int i = begin; i <= end; i++) {
            if (is_possible(index - 1, i == begin && tightleft, i == end && tightright, s - i)) {
                dp2[index][tightleft][tightright][s] = i * base + dp2[index - 1][i == begin && tightleft][i == end && tightright][s - i];
                return possible[index][tightleft][tightright][s] = true;
            }
        }
        return possible[index][tightleft][tightright][s];
    }
}

int main() {
    long long a, b;
    scan(a);
    scan(b);
    scan(S);
    store(a - 1, A);
    store(b, B);

    printf("%lld\n", solve(B) - solve(A));

    store(a, A);

    is_possible(16, true, true, S);
    printf("%lld\n", dp2[16][true][true][S]);

    return 0;
}