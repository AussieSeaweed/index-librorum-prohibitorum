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

int main() {
    int N;
    scanf("%d", &N);
    long long maxx, maxy, maxdist = -inf;
    for (int i = 0; i < N; i++) {
        long long x, y;
        scanf("%lld%lld", &x, &y);
        if (x * x + y * y > maxdist) {
            maxx = x;
            maxy = y;
            maxdist = x * x + y * y;
        }
    }
    printf("%lld %lld\n", maxx, maxy);
    return 0;
}