#include <bits/stdc++.h>
#include <bits/extc++.h>
#define scan(x) do{while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0');}while(0)
char _;
#define INF 9000000000000000000
#define inf 2000000000
using namespace std;

int W, H, N, mat[251][251];

int get_sum(int r1, int c1, int r2, int c2) {
    return mat[r2][c2] - mat[r2][c1 - 1] - mat[r1 - 1][c2] + mat[r1 - 1][c1 - 1];
}

int main() {
    scan(W);
    scan(H);
    scan(N);

    for (int i = 1; i <= H; i++)
        for (int j = 1; j <= W; j++) {
            scan(mat[i][j]);
            mat[i][j] += mat[i - 1][j] + mat[i][j - 1] - mat[i - 1][j - 1];
        }

    int ans = 0;

    for (int i = 1, j = min(N, W); i <= H; i++, j = min(W, N / i)) {
        if (!j) break;
        for (int r = i; r <= H; r++)
            for (int c = j; c <= W; c++)
                ans = max(ans, get_sum(r - i + 1, c - j + 1, r, c));
    }

    printf("%d\n", ans);

    return 0;
}