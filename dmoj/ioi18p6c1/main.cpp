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

int N, Q, mind[5000][5000];
long long dp[5000][5000];

vector<long long> minimum_costs(vector<int> H, vector<int> L, vector<int> R) {
    N = H.size();
    Q = L.size();

    for (int i = 0; i < N; i++) {
        dp[i][i] = H[i];
        mind[i][i] = i;
    }

    for (int offset = 1; offset < N; offset++) {
        for (int i = 0, j = offset; j < N; i++, j++) {
            mind[i][j] = H[mind[i][j - 1]] < H[j] ? j : mind[i][j - 1];
            long long k = mind[i][j];
            dp[i][j] = min(dp[i][k - 1] + H[k] * (j - k + 1), H[k] * (k - i + 1) + dp[k + 1][j]);
        }
    }

    vector<long long> ans(Q);

    for (int i = 0; i < Q; i++)
        ans[i] = dp[L[i]][R[i]];

    return ans;
}

int main() {
    return 0;
}