#include <bits/stdc++.h>
#include <bits/extc++.h>
#define pscan(x) do{while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0');}while(0)
#define scan(x) do{while((x=getchar())<'-'); _ssign=x=='-'; if(_ssign) while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0'); x=_ssign?-x:x;}while(0)
char _; bool _ssign;
template<typename T> inline constexpr const T&_min(const T&x,const T&y) {return x<y?x:y;}
template<typename T> inline constexpr const T&_max(const T&x,const T&y) {return x<y?y:x;}
template<typename T,typename...Ts> inline constexpr const T&_min(const T&x,const Ts&...xs) {return _min(x,_min(xs...));}
template<typename T,typename...Ts> inline constexpr const T&_max(const T&x,const Ts&...xs) {return _max(x,_max(xs...));}
#define min(...) _min(__VA_ARGS__)
#define max(...) _max(__VA_ARGS__)
#define INF 9000000000000000000
#define inf 2000000000
using namespace std;

inline long long powmod(long long base, long long exponent, long long modulus) {
    long long result = 1;
    base %= modulus;
    while (exponent) {
        if (exponent & 1)
            result = result * base % modulus;
        exponent >>= 1;
        base = base * base % modulus;
    }
    return result;
}

long long N, M, K, V, andop[2], orop[2], xorop[2], ans[3] {1, 1, 1};

int main() {
    scan(N);
    scan(M);
    scan(K);
    scan(V);

    xorop[0] = xorop[1] = powmod(2, N - 1, M);

    orop[0] = 1 % M;
    orop[1] = (powmod(2, N, M) - 1 + M) % M;

    andop[0] = (powmod(2, N, M) - 1 + M) % M;
    andop[1] = 1 % M;

    for (int i = 0; i < K; i++) {
        ans[0] = ans[0] * xorop[bool(V & (1ll << i))] % M;
        ans[1] = ans[1] * orop[bool(V & (1ll << i))] % M;
        ans[2] = ans[2] * andop[bool(V & (1ll << i))] % M;
    }

    printf("%lld\n%lld\n%lld\n", ans[0], ans[1], ans[2]);

    return 0;
}