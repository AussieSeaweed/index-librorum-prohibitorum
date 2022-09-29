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
pair<int, int> pts[15000];
int bit[32002], cnt[15000];

inline void update(int i) {
    while (i <= 32002) {
        bit[i]++;
        i += i & -i;
    }
}

inline int query(int i) {
    int ret = 0;
    while (i) {
        ret += bit[i];
        i -= i & -i;
    }
    return ret;
}

int main() {
    scan(N);
    for (int i = 0; i < N; i++) {
        scan(pts[i].first);
        scan(pts[i].second);
        pts[i].second++;
    }
    sort(pts, pts + N);
    for (int i = 0; i < N; i++) {
        int q = query(pts[i].second);
        cnt[q]++;
        update(pts[i].second);
    }
    for (int i = 0; i < N; i++) {
        printf("%d\n", cnt[i]);
    }
    return 0;
}