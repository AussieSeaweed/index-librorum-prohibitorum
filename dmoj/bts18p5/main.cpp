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
#define MOD 998244353
using namespace std;

long long N, mat[2000][2000];

int main() {
    scan(N);
    for (int i = 0; i < N; i++)
        scan(mat[0][i]);

    for (int i = 1; i < N; i++) {
        long long sum = mat[i - 1][i - 1];
        for (int j = i; j < N; j++) {
            mat[i][j] = mat[0][j] * sum % MOD;
            sum = (sum + mat[i - 1][j]) % MOD;
        }
    }

    for (int i = 0; i < N; i++) {
        long long ans = 0;
        for (int j = i; j < N; j++)
            ans = (ans + mat[i][j]) % MOD;
        printf("%lld ", (ans + MOD) % MOD);
    }

    printf("\n");

    return 0;
}