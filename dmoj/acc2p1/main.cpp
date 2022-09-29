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
#define INF 1000000000000000
#define inf 2000000000
using namespace std;

long long N, Q, dist[100][100], dp[100][100][100];

void floyd_warshall() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            dist[i][j] = INF;
        }
    }

    for (int i = 0; i < N; i++) {
        dist[i][i] = 0;
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            int w;
            scan(w);
            if (w) {
                dist[i][j] = w;
            }
        }
    }

    for (int k = 0; k < N; k++) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }
}

long long solve(int s, int t, int d) {
    if (~dp[s][t][d]) return dp[s][t][d];
    if (d == 0) return dp[s][t][d] = s == t ? 0 : INF;

    dp[s][t][d] = INF;

    for (int k = 0; k < N; k++) {
        dp[s][t][d] = min(dp[s][t][d], max(dist[s][k], solve(k, t, d - 1)));
    }

    return dp[s][t][d];
}

int main() {
    scan(N);
    floyd_warshall();
    memset(dp, -1, sizeof dp);
    scan(Q);
    while (Q--) {
        int s, t, d;
        scan(s);
        scan(t);
        scan(d);
        --s;
        --t;
        if (dist[s][t] < INF) {
            printf("%lld\n", solve(s, t, d));
        } else {
            printf("0\n");
        }
    }
    return 0;
}