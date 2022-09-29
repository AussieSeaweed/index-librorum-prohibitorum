#include <iostream>
#include <vector>
using namespace std;

vector<double> dp(1 << 20, -1);
vector<vector<double>> grid(20, vector<double>(20));
int N;

double bit_mask_util(int selected, int bitmask) {
    if (selected == N) return 1.0;
    if (dp[bitmask] != -1) return dp[bitmask];
    double max_val = 0;
    for (int i = 0; i < N; i++) {
        if (bitmask & (1 << i)) {
            max_val = max(max_val, grid[selected][i] * bit_mask_util(selected + 1, bitmask ^ (1 << i)));
        }
    }
    return dp[bitmask] = max_val;
}

int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; i++) for (int j = 0; j < N; j++) scanf("%lf", &grid[i][j]);
    for (int i = 0; i < N; i++) for (int j = 0; j < N; j++) grid[i][j] /= 100.0;
    printf("%lf", bit_mask_util(0, (1 << N) - 1) * 100);
    return 0;
}