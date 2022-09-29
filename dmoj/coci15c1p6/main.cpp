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

int N, v[10001];
vector<int> sub_intervals[101];
bitset<101> possible[101];
vector<pair<int, int>> intervals[10001];
vector<int> graph[10001];

int solve(int node) {
    for (int adj : graph[node]) {
        solve(adj);
    }

    for (int i = 1; i <= 100; i++) {
        sub_intervals[i].clear();
        possible[i].reset();
    }

    for (int adj : graph[node]) {
        for (pair<int, int> &interval : intervals[adj])
            sub_intervals[interval.first].push_back(interval.second);
    }

    for (int lo = 100; lo >= 1; lo--) {
        if (lo == v[node]) {
            possible[lo] |= possible[lo + 1];
            possible[lo][lo] = true;
        } else {
            for (int hi : sub_intervals[lo]) {
                if ((lo < v[node] && hi < v[node]) || (v[node] < lo && v[node] < hi)) {
                    possible[lo] |= possible[hi + 1];
                    possible[lo][hi] = true;
                }
            }
        }

        if (lo <= v[node])
            for (int hi = v[node]; hi <= 100; hi++)
                if (possible[lo][hi])
                    intervals[node].emplace_back(lo, hi);
    }

    return intervals[node].size();
}

int main() {
    scan(N);

    for (int i = 1; i <= N; i++)
        scan(v[i]);

    for (int i = 1; i < N; i++) {
        int a, b;
        scan(a);
        scan(b);
        graph[a].push_back(b);
    }

    printf("%d\n", solve(1));

    return 0;
}