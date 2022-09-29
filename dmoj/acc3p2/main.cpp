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

struct Point {
    long long x, y;
    Point(long long x, long long y) : x{ x }, y{ y } {}
};

int N;
Point *pts[1000000];
long long x[1000000], y[1000000];

int main() {
    pscan(N);

    for (int i = 0; i < N; i++) {
        long long xv, yv;
        scan(xv);
        scan(yv);
        pts[i] = new Point(xv, yv);
        x[i] = xv + yv, y[i] = xv - yv;
    }

    sort(x, x + N), sort(y, y + N);

    long long ym = (x[N / 2] - y[N / 2]) / 2, xm = y[N / 2] + ym;
    long long ans = INF;

    for (int xo = -1; xo <= 1; xo++) {
        for (int yo = -1; yo <= 1; yo++) {
            long long cur = 0;
            long long xn = xm + xo, yn = ym + yo;

            for (int i = 0; i < N; i++) {
                cur += max(abs(pts[i]->x - xn), abs(pts[i]->y - yn));
            }

            ans = min(ans, cur);
        }
    }

    printf("%lld\n", ans);

    return 0;
}