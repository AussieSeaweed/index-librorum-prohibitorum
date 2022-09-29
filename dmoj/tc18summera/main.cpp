#include <stdio.h>

int main() {
    long long N, B, A;
    scanf("%lld%lld%lld", &N, &B, &A);

    if (B != 0) {
        long long x = (B * N - A) / (2 * B);
        long long a1 = (N - x) * (B * x + A);
        long long a2 = (N - (x + 1)) * (B * (x + 1) + A);
        printf("%lld", a1 > a2 ? a1 : a2);
    } else {
        printf("%lld", A * N);
    }
    return 0;
}