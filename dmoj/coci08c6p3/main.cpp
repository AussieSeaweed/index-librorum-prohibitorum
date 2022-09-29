#include <bits/stdc++.h>
#define scan(x) do{while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0');}while(0)
char _;
#define INF 9000000000000000000
#define inf 2000000000
using namespace std;

int N, M;
vector<pair<int, int>> dimensions;
int cnt[101][101];

void get_dimensions(int N) {
    for (int i = 1; i <= N; i++)
        for (int j = i; j <= N; j++)
            if (i * j == M) {
                dimensions.emplace_back(i, j);
                if (i != j)
                    dimensions.emplace_back(j, i);
            }
}

int main() {
    scan(N);
    scan(M);

    get_dimensions(N);

    for (int i = 0; i < M; i++) {
        int r, c;
        scan(r);
        scan(c);

        cnt[r][c] = 1;
    }

    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= N; j++)
            cnt[i][j] += cnt[i][j - 1] + cnt[i - 1][j] - cnt[i - 1][j - 1];

    int ans = 0;

    for (pair<int, int> dimension : dimensions) {
        int w = dimension.first, h = dimension.second;
        for (int i = w; i <= N; i++) {
            for (int j = h; j <= N; j++) {
                ans = max(ans, cnt[i][j] - cnt[i - w][j] - cnt[i][j - h] + cnt[i - w][j - h]);
            }
        }
    }

    printf("%d\n", M - ans);

    return 0;
}