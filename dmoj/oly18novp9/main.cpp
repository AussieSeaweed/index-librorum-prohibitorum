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

int digits[10];
int dp[11][10];

int solve(int len, int previous, bool tight) {
    if (!tight && ~dp[len][previous]) return dp[len][previous];
    if (len == 0) return (tight ? 1 : dp[len][previous] = 1);
    int ret = 0, lim = tight ? digits[len - 1] : 9;

    for (int digit = 0; digit <= min(lim, previous - 2); digit++) {
        ret += solve(len - 1, digit, tight && digit == lim);
    }

    for (int digit = previous + 2; digit <= lim; digit++) {
        ret += solve(len - 1, digit, tight && digit == lim);
    }

    if (!tight) dp[len][previous] = ret;

    return ret;
}

int solve(int num) {
    int i = 0;
    while (num) {
        digits[i++] = num % 10;
        num /= 10;
    }
    int ret = 0;
    for (int len = 1; len <= i; len++) {
        int lim = len == i ? digits[i - 1] : 9;
        for (int digit = 1; digit <= lim; digit++) {
            ret += solve(len - 1, digit, len == i && digit == lim);
        }
    }
    return ret;
}

int main() {
    memset(dp, -1, sizeof dp);
    int L, R;
    scan(L);
    scan(R);
    printf("%d\n", solve(R) - solve(L - 1));
    return 0;
}