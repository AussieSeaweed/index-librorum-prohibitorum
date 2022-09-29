#include <iostream>
#include <vector>
using namespace std;

int main() {
    int _;
    scanf("%d", &_);
    while (_--) {
        int n, k, w;
        scanf("%d%d%d", &n, &k, &w);
        vector<int> pins(n + 1);
        vector<int> spins(n + 1);
        vector<vector<int>> best(k + 1, vector<int>(n + 1));
        for (int i = 1; i <= n; i++) scanf("%d", &pins[i]);
        for (int i = 1; i <= n; i++) spins[i] = pins[i] + spins[i - 1];
        int ans = 0;
        for (int t = 1; t <= k; t++) {
            int most = 0;
            for (int i = w * t; i <= n; i++) {
                most = max(most, best[t - 1][i - w]);
                best[t][i] = most + spins[i] - spins[i - w];
                ans = max(ans, best[t][i]);
            }
        }

        printf("%d\n", ans);
    }
    return 0;
}