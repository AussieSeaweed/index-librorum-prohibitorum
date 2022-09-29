#include <bits/stdc++.h>

int main() {
    int N, M;
    scanf("%d%d", &N, &M);

    if (N % M == 0) {
        printf("yes %d", N/M);
    } else {
        int i;
        for (i = M; i <= N; i++) {
            if (N % i == 0) break;
        }
        printf("no %d", i-M);
    }
    return 0;
}