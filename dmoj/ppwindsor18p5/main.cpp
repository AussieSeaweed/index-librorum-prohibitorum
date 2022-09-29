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

int N;

int main() {
    scan(N);

    long long lo = 1, hi = 10, len = 1, base = 1;

    while (hi <= N) {
        len++;
        base *= 10;
        lo = hi;
        hi = 9 * base * len + lo;
    }

    long long cur = base;
    N -= lo - 1;

    while (len < N) {
        cur++;
        N -= len;
    }

    deque<long long> digits;

    while (cur) {
        digits.push_front(cur % 10);
        cur /= 10;
    }

    printf("%lld\n", digits[N - 1]);

    return 0;
}