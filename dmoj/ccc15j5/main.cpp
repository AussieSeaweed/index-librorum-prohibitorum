#include <iostream>

int options[251][251];
int N, K;

int getnum(int n, int k) {
    if (n < k)
        return 0;
    if (n == k || k == 1)
        return 1;
    if (options[n][k] != -1)
        return options[n][k];
    options[n][k] = getnum(n-1, k-1) + getnum(n-k, k);
    return options[n][k];
}

int main() {
    scanf("%d%d", &N, &K);
    for (int i = 0; i <= N; i++)
        for (int j = 0; j <= K; j++)
            options[i][j] = -1;
    printf("%d\n", getnum(N, K));
    return 0;
}