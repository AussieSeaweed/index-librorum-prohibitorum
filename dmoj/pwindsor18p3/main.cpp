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

bool prime[1000001];

void get_primes() {
    fill(prime, prime + 1000001, true);
    prime[0] = prime[1] = false;

    for (long long i = 2; i <= 1000000; i++)
        if (prime[i])
            for (long long j = i * i; j <= 1000000; j += i)
                prime[j] = false;
}

int main() {
    get_primes();
    int N, cnt = 0;
    scan(N);
    while (N--) {
        int n;
        scan(n);
        if (!prime[n])
            cnt++;
    }
    printf("%d\n", cnt);
    return 0;
}