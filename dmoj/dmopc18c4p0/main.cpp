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

int R, X, Y;

struct Star {
    int x, y, m;
    bool operator<(const Star &that) const {
        return m < that.m;
    }
} stars[3];

int dist() {
    int dx = X - stars[0].x, dy = Y - stars[0].y;
    return dx * dx + dy * dy;
}

int main() {
    scan(R);
    scan(X);
    scan(Y);

    scanf("%d%d%d%d%d%d%d%d%d", &stars[0].x, &stars[0].y, &stars[0].m, &stars[1].x, &stars[1].y, &stars[1].m, &stars[2].x, &stars[2].y, &stars[2].m);
    sort(stars, stars + 3);

    printf(dist() < R * R ? "What a beauty!" : "Time to move my telescope!");

    return 0;
}