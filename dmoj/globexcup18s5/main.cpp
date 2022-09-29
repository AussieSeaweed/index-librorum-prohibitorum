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

long long N, bit[501][250101], K, p[501][501], a[501][501];

int inv(int i) { return 250101 - i; }

int query(int i, int j) {
    int ret = 0;

    for (int p = i; p; p -= p & -p)
        for (int q = j; q; q -= q & -q)
            ret += bit[p][q];

    return ret;
}

void update(int i, int j) {
    for (int p = i; p <= 500; p += p & -p)
        for (int q = j; q < 250101; q += q & -q)
            bit[p][q]++;
}

int main() {
    scan(N);

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            scan(p[i][j]);
            int k = query(j - 1, inv(p[i][j]));
            K += k;
            a[i][j] = p[i][j] + k;
        }

        for (int j = 1; j <= N; j++) {
            update(j, inv(a[i][j]));
        }
    }

    printf("%lld\n", K);

    return 0;
}