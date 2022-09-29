#include <bits/stdc++.h>
#define scan(x) do{while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0');}while(0)
char _;
#define INF 9000000000000000000
#define inf 2000000000
using namespace std;

double dp[21][20001];
bool visited[21][20001];

void reset() {
    memset(visited, 0, sizeof visited);
}

double solve(int x, int h, int X, int Y) { // X and Y are constant
    if (h <= 0) return 1;
    if (visited[x][h]) return dp[x][h];
    visited[x][h] = true;
    if (x == X) return dp[x][h] = 0;
    dp[x][h] = 0;

    for (int i = 1; i <= Y; i++) {
        dp[x][h] += (1. / Y) * solve(x + 1, h - i, X, Y);
    }

    return dp[x][h];
}

tuple<int, int, int> get_values(string &str) {
    int X = 0, Y = 0, Z = 0, sign = 1;
    int *cur = &X;

    for (char ch : str) {
        if (ch == 'd') {
            cur = &Y;
        } else if (ch == '-' || ch == '+') {
            cur = &Z;
            sign = ch == '-' ? -1 : 1;
        } else {
            *cur = *cur * 10 + (ch - '0');
        }
    }

    return {X, Y, sign * Z};
}

int main() {
    int T;
    scan(T);

    for (int i = 1; i <= T; i++) {
        int H, S;
        scan(H);
        scan(S);

        double ans = 0;

        while (S--) {
            string str;
            cin >> str;

            int X, Y, Z;
            tuple<int, int, int> values = get_values(str);
            X = get<0>(values), Y = get<1>(values), Z = get<2>(values);

            reset();
            ans = max(ans, solve(0, H - Z, X, Y));
        }

        printf("Case #%d: %lf\n", i, ans);
    }

    return 0;
}