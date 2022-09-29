#include <iostream>
#include <cmath>

int main() {
    int N;
    scanf("%d", &N);
    double ans = 0;
    while (N--) {
        double in;
        scanf("%lf", &in);
        ans += pow(log(2) / log(in), -1);
    }
    printf("%d", ((int) ans) + 1);
    return 0;
}