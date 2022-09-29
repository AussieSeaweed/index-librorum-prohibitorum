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


int N, bit[100001], dp[100000];
pair<int, int> pts[100000];

int query(int i) {
    int ret = 0;

    while (i) {
        ret = max(ret, bit[i]);
        i -= i & -i;
    }

    return ret;
}

void update(int i, int val) {
    while (i <= 100000) {
        if (val > bit[i])
            bit[i] = val;
        else break;
        i += i & -i;
    }
}

int main() {
    scan(N);

    for (int i = 0; i < N; i++) {
        scan(pts[i].first);
        scan(pts[i].second);
    }

    sort(pts, pts + N);

    int ans = 0;

    for (int lo = 0, hi = 0; hi < N; hi++) {
        if (pts[lo].first != pts[hi].first) {
            for (int i = lo; i < hi; i++) {
                update(pts[i].second, dp[i]);
            }

            lo = hi;
        }

        ans = max(ans, dp[hi] = 1 + query(pts[hi].second - 1));
    }

    printf("%d\n", ans);

    return 0;
}