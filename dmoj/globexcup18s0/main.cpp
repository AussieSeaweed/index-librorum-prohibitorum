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

int N;
pair<long long, long long> pts[100000];
long long x[100000], y[100000];

int main() {
    scan(N);

    for (int i = 0; i < N; i++) {
        scan(x[i]);
        scan(y[i]);
        pts[i].first = x[i], pts[i].second = y[i];
    }

    sort(x, x + N);
    sort(y, y + N);

    long long ans = 0;

    for (int i = 0; i < N; i++) {
        ans += abs(pts[i].first - x[N / 2]) + abs(pts[i].second - y[N / 2]);
    }

    printf("%lld\n", ans);

    return 0;
}