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

bool s[1001];

int sieve(int N, int K) {
    fill(s, s + N + 1, true);

    for (int i = 2; i <= N; i++) {
        if (s[i]) {
            K--;
            if (!K) return i;
            for (int j = i * i; j <= N; j += i) {
                if (s[j]) {
                    s[j] = false;
                    K--;
                    if (!K) return j;
                }
            }
        }
    }
}

int main() {
    int N, K;
    scan(N);
    scan(K);
    printf("%d\n", sieve(N, K));
    return 0;
}