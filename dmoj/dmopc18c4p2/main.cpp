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

int N, sum = 0;
bool reachable[490001];

int main() {
    scan(N);
    reachable[0] = true;

    for (int i = 0; i < N; i++) {
        int val;
        scan(val);
        sum += val;
        for (int j = 490000; j >= val; j--) {
            if (reachable[j - val]) {
                reachable[j] = true;
            }
        }
    }
    int lim = sum / 2 + sum % 2;
    for (int d = 0; d <= lim; d++) {
        if (reachable[sum / 2 - d] || reachable[sum / 2 + d]) {
            printf("%d\n", 2 * d + sum % 2);
            return 0;
        }
    }

    return 0;
}