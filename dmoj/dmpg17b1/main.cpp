#include <bits/stdc++.h>

int main() {
    int N;
    scanf("%d", &N);

    int minc, maxd = -INFINITY;

    while (N--) {
        int c, d;
        scanf("%d%d", &c, &d);
        if (d > maxd) {
            maxd = d;
            minc = c;
        } else if (d == maxd) {
            minc = std::min(c, minc);
        }
    }

    printf("%d %d", minc, maxd);
}