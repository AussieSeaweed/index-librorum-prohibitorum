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

struct Box {
    int l, w, h, i;
    long long p;
    bool operator<(const Box &that) const {
        return h == that.h ? (l == that.l ? w < that.w : l < that.l) : h < that.h;
    }
};

int N;
Box boxes[100001];
int bit[5001][5001], pred[100001], cnt[100001], used[100000];
long long dp[100001];

int query(int r, int c) {
    int ret = 0;

    for (int i = r; i; i -= i & -i)
        for (int j = c; j; j -= j & -j)
            ret = dp[bit[i][j]] > dp[ret] ? bit[i][j] : ret;

    return ret;
}

void update(int r, int c, int value) {
    for (int i = r; i <= 5000; i += i & -i)
        for (int j = c; j <= 5000; j += j & -j)
            bit[i][j] = dp[bit[i][j]] > dp[value] ? bit[i][j] : value;
}

int main() {
    scan(N);

    for (int i = 1; i <= N; i++) {
        scan(boxes[i].l);
        scan(boxes[i].w);
        scan(boxes[i].h);
        scan(boxes[i].p);
        if (boxes[i].l > boxes[i].w) swap(boxes[i].l, boxes[i].w);
        boxes[i].i = i;
    }

    sort(boxes + 1, boxes + N + 1);

    long long last_ind = 0;

    for (int i = 1; i <= N; i++) {
        int previous = query(boxes[i].l, boxes[i].w);
        dp[i] = boxes[i].p + dp[previous];
        if (dp[i] > dp[last_ind]) last_ind = i;
        pred[i] = previous;
        cnt[i] = cnt[previous] + 1;
        update(boxes[i].l, boxes[i].w, i);
    }

    printf("%lld\n", dp[last_ind]);

    int i = 0, n = cnt[last_ind];

    while (last_ind) {
        used[i++] = boxes[last_ind].i;
        last_ind = pred[last_ind];
    }

    printf("%d\n", n);

    for (int i = 0; i < n; i++)
        printf("%d ", used[i]);
    printf("\n");

    return 0;
}