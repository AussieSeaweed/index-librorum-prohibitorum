#include <iostream>
using namespace std;

int dp[32];
int N;

int get(int n) {
    int i = 0, ret = 0;
    while (n) {
        if (n & 1)
            ret = max(ret, dp[i]);
        n >>= 1;
        i++;
    }
    return ret;
}

void store(int n, int val) {
    int i = 0;
    while (n) {
        if (n & 1)
            dp[i] = max(dp[i], val);
        n >>= 1;
        i++;
    }
}

int main() {
    scanf("%d", &N);
    int ans = 1;
    while (N--) {
        int n;
        scanf("%d", &n);
        int val = get(n) + 1;
        ans = max(ans, val);
        store(n, val);
    }
    printf("%d", ans);
    return 0;
}