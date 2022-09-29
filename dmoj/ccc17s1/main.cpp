#include <bits/stdc++.h>

int swifts[100001];
int sophomores[100001];
int N;

int main() {
    scanf("%d", &N);
    swifts[0] = 0;
    sophomores[0] = 0;
    int x;
    for (int i = 1; i <= N; i++) {
        scanf("%d", &x);
        swifts[i] = swifts[i-1] + x;
    }

    for (int i = 1; i <= N; i++) {
        scanf("%d", &x);
        sophomores[i] = sophomores[i-1] + x;
    }

    int max = 0;
    for (int i = 1; i <= N; i++) {
        if (swifts[i] == sophomores[i])
            max = i;
    }

    printf("%d\n", max);
    return 0;
}