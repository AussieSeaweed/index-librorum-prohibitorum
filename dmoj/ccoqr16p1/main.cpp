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
long long ans = 0;
pair<int, int> pts[100000];
map<int, vector<int> *> xmap, ymap;

int main() {
    scan(N);

    for (int i = 0; i < N; i++) {
        int x, y;
        scan(x);
        scan(y);

        if (xmap[x])
            xmap[x]->push_back(y);
        else
            xmap[x] = new vector<int> {y};

        if (ymap[y])
            ymap[y]->push_back(x);
        else
            ymap[y] = new vector<int> {x};

        pts[i] = {x, y};
    }

    for (const pair<int, vector<int> *> &items : xmap) {
        sort(items.second->begin(), items.second->end());
    }

    for (const pair<int, vector<int> *> &items : ymap) {
        sort(items.second->begin(), items.second->end());
    }

    for (int i = 0; i < N; i++) {
        auto xbegin = xmap[pts[i].first]->begin(), xend = xmap[pts[i].first]->end(),
                ybegin = ymap[pts[i].second]->begin(), yend = ymap[pts[i].second]->end();
        long long A = lower_bound(xbegin, xend, pts[i].second) - xbegin, B = xend - upper_bound(xbegin, xend, pts[i].second),
                C = lower_bound(ybegin, yend, pts[i].first) - ybegin, D = yend - upper_bound(ybegin, yend, pts[i].first);
        ans += 2ll * A * B * C * D;
    }

    printf("%lld\n", ans);

    return 0;
}