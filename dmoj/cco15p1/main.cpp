#include <bits/stdc++.h>
#include <bits/extc++.h>
#define scan(x) do{while((x=getchar())<'-'); _ssign=x=='-'; if(_ssign) while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0'); x=_ssign?-x:x;}while(0)
char _; bool _ssign;
template<typename T>constexpr const T&_min(const T&x,const T&y) {return x<y?x:y;}
template<typename T>constexpr const T&_max(const T&x,const T&y) {return x<y?y:x;}
template<typename T,typename...Ts> constexpr const T&_min(const T&x,const Ts&...xs) {return _min(x,_min(xs...));}
template<typename T,typename...Ts> constexpr const T&_max(const T&x,const Ts&...xs) {return _max(x,_max(xs...));}
#define min(...) _min(__VA_ARGS__)
#define max(...) _max(__VA_ARGS__)
#define INF 9000000000000000000
#define inf 2000000000
using namespace std;

int N, W;
long long crackers[100000];

long long get_min_ans() {
    if (crackers[0] <= W && W <= crackers[N - 1]) {
        return crackers[N - 1] - crackers[0];
    } else if (W < crackers[0]) {
        return crackers[N - 1] - W;
    } else {
        return W - crackers[0];
    }
}

int main() {
    scan(N);
    scan(W);

    for (int i = 0; i < N; i++)
        scan(crackers[i]);

    sort(crackers, crackers + N);
    long long min_ans = get_min_ans(), a1 = 0, a2 = 0, prev = W;
    int i = 0, lo = 0, hi = N - 1;

    while (lo <= hi) {
        if (i++ & 1) {
            a1 += max(abs(crackers[lo] - W), abs(crackers[lo] - prev));
            prev = crackers[lo];
            lo++;
        } else {
            a1 += max(abs(crackers[hi] - W), abs(crackers[hi] - prev));
            prev = crackers[hi];
            hi--;
        }
    }

    i = 0, lo = 0, hi = N - 1, prev = W;

    while (lo <= hi) {
        if (i++ & 1) {
            a2 += max(abs(crackers[hi] - W), abs(crackers[hi] - prev));
            prev = crackers[hi];
            hi--;
        } else {
            a2 += max(abs(crackers[lo] - W), abs(crackers[lo] - prev));
            prev = crackers[lo];
            lo++;
        }
    }
    printf("%lld %lld\n", min_ans, max(a1, a2));

    return 0;
}