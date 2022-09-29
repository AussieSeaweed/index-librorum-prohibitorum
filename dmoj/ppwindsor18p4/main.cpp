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

long long N, empty[1000], hate[3000];

int main() {
    int N, M;
    scan(N);
    scan(M);

    for (int i = 0; i < N; i++)
        scan(empty[i]);

    for (int i = 0; i < M; i++)
        scan(hate[i]);

    long long ans = -1, val = -INF;

    for (int i = 0; i < N; i++) {
        long long cur = INF;

        for (int j = 0; j < M; j++) {
            cur = min(cur, abs(hate[j] - empty[i]));
        }

        if (val < cur) {
            ans = i;
            val = cur;
        }
    }

    printf("%lld\n", empty[ans]);

    return 0;
}