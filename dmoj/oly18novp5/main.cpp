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

int N, K;
long long dp[100002], elems[100001];
deque<int> brkpts;

int main() {
    scan(N);
    scan(K);
    for (int i = 1; i <= N; i++) {
        scan(elems[i]);
        elems[i] += elems[i - 1];
    }
    brkpts.push_back(0);
    for (int i = 1; i <= N; i++) {
        dp[i + 1] = -inf;
        while (brkpts.front() < i - K) brkpts.pop_front();
        dp[i + 1] = dp[brkpts[0]] + elems[i] - elems[brkpts[0]];
        while (!brkpts.empty() && (dp[brkpts.back()] + elems[i] - elems[brkpts.back()] < dp[i])) brkpts.pop_back();
        brkpts.push_back(i);
    }
    printf("%lld\n", dp[N + 1]);
    return 0;
}