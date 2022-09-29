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

bool is_prime[100000001];
int cnt[10000001], T;

void sieve() {
    fill(is_prime, is_prime + 10000001, true);
    for (int i = 2; i <= 10000000; i++) {
        if (is_prime[i]) {
            for (int j = i; j <= 10000000; j += i) {
                is_prime[j] = false;
                cnt[j]++;
            }
        }
    }
}

int main() {
    sieve();
    scan(T);

    for (int t = 1; t <= T; t++) {
        int A, B, K;
        scan(A);
        scan(B);
        scan(K);

        int ans = 0;

        for (int i = A; i <= B; i++) {
            if (cnt[i] == K) ans++;
        }

        printf("Case #%d: %d\n", t, ans);
    }

    return 0;
}