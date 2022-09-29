#include <iostream>
#include <algorithm>
#include <cmath>
#define inf 2000000000
using namespace std;

std::pair<int, int> da[1000];
int dp[1000][2], N, I, D, S;

bool reachable(int i, int j, bool a, bool b) {
    int d1 = da[i].first, d2 = da[j].first, a1 = da[i].second - (a ? S : 0), a2 = da[j].second - (b ? S : 0);
    if (a1 < 0 || a2 < 0) return false;
    if (a1 == a2) return true;
    else if (a1 < a2) return I && (d2 - d1) >= (a2 - a1) / I + min(1, (a2 - a1) % I);
    else return D && (d2 - d1) >= (a1 - a2) / D + min(1, (a1 - a2) % D);
}

int solve() {
    int ret = 0;

    for (int i = 0; i < N; i++) {
        if (!da[i].second || (I && da[i].first >= da[i].second / I + min(1, da[i].second % I)))
            dp[i][0] = 1;
        else
            dp[i][0] = -inf;
        if (da[i].second >= S && (!(da[i].second - S) || (I && da[i].first >= (da[i].second - S) / I + min(1, (da[i].second - S) % I))))
            dp[i][1] = 1;
        else
            dp[i][1] = -inf;

        for (int j = 0; j < i; j++) {
            if (reachable(j, i, false, false)) {
                dp[i][0] = max(dp[i][0], dp[j][0] + 1);
            }
            if (reachable(j, i, true, false)) {
                dp[i][0] = max(dp[i][0], dp[j][1] + 1);
            }
            if (reachable(j, i, false, true)) {
                dp[i][1] = max(dp[i][1], dp[j][0] + 1);
            }
            if (reachable(j, i, true, true)) {
                dp[i][1] = max(dp[i][1], dp[j][1] + 1);
            }
        }
        ret = max(ret, max(dp[i][0], dp[i][1]));
    }

    return ret;
}

int main() {
    scanf("%d%d%d%d", &N, &I, &D, &S);

    for (int i = 0; i < N; i++) {
        scanf("%d%d", &da[i].first, &da[i].second);
    }

    sort(da, da + N);

    printf("%d\n", solve());

    return 0;
}