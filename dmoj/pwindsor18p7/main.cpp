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
#define inf 100000000
#define MOD 1000000007
using namespace std;

struct COMPARE {
    long long combine(long long a, long long b) {
        long long tmp = b, base = 1;
        while (tmp) {
            base *= 10;
            tmp /= 10;
        }

        return a * base + b;
    }

    bool operator()(long long a, long long b) {
        long long ab = combine(a, b), ba = combine(b, a);
        return ab > ba;
    }
};

int N;
long long nums[10000];

int main() {
    scan(N);

    for (int i = 0; i < N; i++) {
        scan(nums[i]);
    }

    sort(nums, nums + N, COMPARE());

    for (int i = 0; i < N; i++) {
        printf("%lld", nums[i]);
        fflush(stdout);
    }

    return 0;
}