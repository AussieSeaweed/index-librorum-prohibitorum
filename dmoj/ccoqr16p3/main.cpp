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

int N, M;
pair<long long, long long> blocks[100000];

int main() {
    scan(N);
    scan(M);

    for (int i = 0; i < M; i++) {
        scan(blocks[i].second);
        scan(blocks[i].first);
        blocks[i].second = N - blocks[i].second + 1;
    }

    sort(blocks, blocks + M);

    long long pr = blocks[0].second, pc = blocks[0].first;
    long long ans = blocks[0].second;

    for (int i = 1; i < M; i++) {
        long long r = blocks[i].second, c = blocks[i].first;
        long long curr = pr - (c - pc), endc = pc + pr - 1;

        if (c <= endc) {
            if (r <= curr) {
                ans += (c - pc) * (curr + pr - 1) / 2;
                r = curr;
            } else {
                ans += (c - pc - 1) * (pr - 1 + curr + 1) / 2 +  r;
            }
        } else {
            ans += (pr - 1) * pr / 2 + r;
        }

        pr = r, pc = c;
    }

    ans += (pr - 1) * pr / 2;

    printf("%lld\n", ans);

    return 0;
}