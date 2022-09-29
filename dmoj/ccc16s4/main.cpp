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

int N, values[401], ans = 0;
bool dp[401][401];

int main() {
    scan(N);

    for (int i = 1; i <= N; i++) {
        scan(values[i]);
        dp[i][i] = true;
        ans = max(ans, values[i]);
        values[i] += values[i - 1];
    }

    for (int offset = 1; offset < N; offset++) {
        for (int i = 1, j = i + offset; j <= N; i++, j++) {
            int l = i, r = j;
            while (l < r && !dp[i][j]) {
                int left = values[l] - values[i - 1], right = values[j] - values[r - 1];
                if (left == right) {
                    if (dp[i][l] && (l + 1 == r ? true : dp[l + 1][r - 1]) && dp[r][j]) {
                        dp[i][j] = true;
                        ans = max(ans, values[j] - values[i - 1]);
                    }
                    l++, r--;
                } else if (left < right) {
                    l++;
                } else if (left > right) {
                    r--;
                }
            }
        }
    }

    printf("%d\n", ans);

    return 0;
}