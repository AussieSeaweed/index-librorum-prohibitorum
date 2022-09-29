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

int N, K;
vector<pair<long long, long long>> neg, pos;

long long solve(vector<pair<long long, long long>> &houses) {
    if (houses.empty()) return 0;
    long long ret = 0;

    bool start = true;
    long long rem, cur_end;

    while (!houses.empty()) {
        if (start) {
            rem = K;
            cur_end = houses.back().first;
            start = false;
        } else {
            if (rem >= houses.back().second) {
                rem -= houses.back().second;
                houses.pop_back();
            } else {
                houses.back().second -= rem;
                ret += cur_end;
                long long iterations = houses.back().second / K;
                ret += iterations * houses.back().first;
                houses.back().second -= iterations * K;
                start = true;
            }
        }

        if (houses.back().second == 0) houses.pop_back();
    }

    if (!start) ret += cur_end;

    return ret * 2;
}

int main() {
    scan(N);
    scan(K);

    while (N--) {
        long long x, m;
        scanf("%lld", &x);
        scan(m);

        if (x > 0)
            pos.emplace_back(x, m);
        else if (x < 0)
            neg.emplace_back(-x, m);
    }

    sort(neg.begin(), neg.end());
    sort(pos.begin(), pos.end());

    printf("%lld\n", solve(neg) + solve(pos));
    return 0;
}