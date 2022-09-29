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

int N, M[100000];
double total = 0;

bool is_valid(double average) {
    double current = 0, maximum = -inf;

    for (int i = 1; i < N - 1; i++) {
        current += M[i] - average;
        maximum = max(maximum, current);
        if (current < 0) current = 0;
    }

    return maximum >= total - average * N;
}

int main() {
    scan(N);

    for (int i = 0; i < N; i++) {
        scan(M[i]);
        total += M[i];
    }

    double lo = 1, hi = 10000;

    while (hi - lo >= 1e-4) {
        double mid = (lo + hi) / 2;

        if (is_valid(mid)) {
            hi = mid;
        } else {
            lo = mid;
        }
    }

    printf("%.3lf\n", lo);

    return 0;
}