#include <bits/stdc++.h>

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int N;
        scanf("%d", &N);
        int m;
        scanf("%d", &m);

        int count = 0;

        for (int i = 1; i < N; i++) {
            int now;
            scanf("%d", &now);
            if (now > m)
                count++;
        }

        printf("Bob wins $%.2lf at IOI!\n", round(sqrt(N - count) * 100 * 100) / 100);
    }

    return 0;
}