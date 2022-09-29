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

int N, M;
long long a[100000], A = 0, b[100000], B = 0;

int main() {
    scan(N);
    scan(M);

    for (int i = 0; i < N; i++) {
        int s, p;
        scan(s);
        scan(p);
        if (p == 1) {
            a[A++] = s;
        } else {
            b[B++] = s;
        }
    }

    sort(a, a + A);
    sort(b, b + B);

    for (int i = 1; i < A; i++) {
        a[i] += a[i - 1];
    }

    for (int i = 1; i < B; i++) {
        b[i] += b[i - 1];
    }

    long long ans = upper_bound(a, a + A, M) - a;

    for (int i = 0; i < B; i++) {
        if (b[i] <= M) {
            ans = max(ans, (i + 1ll) * 2 + (upper_bound(a, a + A, M - b[i]) - a));
        } else {
            break;
        }
    }

    printf("%lld\n", ans);

    return 0;
}