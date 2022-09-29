#include <bits/stdc++.h>
#include <bits/extc++.h>
#define scan(x) do{while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0');}while(0)
char _;
#define INF 9000000000000000000
#define inf 2000000000
using namespace std;

int val[1000], dp[2][1000][1000], cnt = 0, N, total;

int solve(int t, int i, int j) {
    int &cur = dp[t][i][j];

    if (~cur)
        return cur;
    else if (i == j)
        return cur = t ? 0 : val[i];

    if (t)
        return cur = val[i] >= val[j] ? solve(0, i + 1, j) : solve(0, i, j -1);
    else
        return cur = max(solve(1, i + 1, j) + val[i], solve(1, i, j - 1) + val[j]);
}

int main() {
    while (true) {
        scan(N);

        if (!N) break;

        for (int i = 0; i < 2; i++)
            for (int j = 0; j < N; j++)
                for (int k = j + 1; k < N; k++)
                    dp[i][j][k] = -1;

        total = 0;

        for (int i = 0; i < N; i++) {
            scan(val[i]);
            total += val[i];
            dp[0][i][i] = val[i];
        }

        int query = solve(0, 0, N - 1);

        printf("In game %d, the greedy strategy might lose by as many as %d points.\n", ++cnt, query - total + query);
    }

    return 0;
}