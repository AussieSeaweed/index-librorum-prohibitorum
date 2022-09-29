#include <stdio.h>

int main() {
    int C, D, E;
    scanf("%d%d%d", &C, &D, &E);
    long long ans = 1;
    for (int i = 0; i < 30 && ans; i++) {
        int c = C & (1 << i);
        int d = D & (1 << i);
        int e = E & (1 << i);
        if (c && !d && e) {
            ans *= 2;
        } else if (!((c && d && !e) || (!c && !d && !e))) {
            ans = 0;
        }
    }
    printf("%lld", ans);
    return 0;
}