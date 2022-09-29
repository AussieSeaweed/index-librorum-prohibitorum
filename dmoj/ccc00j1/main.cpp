#include <bits/stdc++.h>

int main() {
    int s, n;
    scanf("%d%d", &s, &n);

    printf("Sun Mon Tue Wed Thr Fri Sat\n");

    for (int i = 0; i < s-1; i++) {
        printf("    ");
    }

    int day = 1;
    int position = s;
    for (; day <= n; day++) {
        if (day >= 10) {
            printf(" %d", day);
        } else {
            printf("  %d", day);
        }
        if (position == 7) {
            if (day != n) {
                printf("\n");
                position = 1;
            }
        } else {
            if (day != n) {
                printf(" ");
                position++;
            }
        }
    }

    printf("\n");
    return 0;
}