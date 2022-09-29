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

long long N, nums[18];

int main() {
    scan(N);
    if (N >= 18) {
        printf("999999998\n");
        return 0;
    }
    nums[1] = 9, nums[2] = 9;
    for (int i = 3; i <= N; i++)
        if (i & 1)
            nums[i] = nums[i - 1] * 10 % 1000000000;
        else
            nums[i] = nums[i - 1];
    long long ans = 0;
    for (int i = 1; i <= N; i++)
        ans = (ans + nums[i]) % 1000000000;
    printf("%lld\n", ans);
    return 0;
}