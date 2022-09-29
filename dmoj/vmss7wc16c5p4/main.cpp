#include <iostream>
#include <vector>

int main() {
    int N;
    scanf("%d", &N);
    std::vector<int> count(N + 1, -1);
    int X, Y, Z;
    scanf("%d%d%d", &X, &Y, &Z);

    count[0] = 0;

    for (int i = 0; i <= N; i++) {
        if (count[i] != -1) {
            if (i + X <= N)
                count[i + X] = std::max(count[i + X], count[i] + 1);
            if (i + Y <= N)
                count[i + Y] = std::max(count[i + Y], count[i] + 1);
            if (i + Z <= N)
                count[i + Z] = std::max(count[i + Z], count[i] + 1);
        }
    }

    printf("%d", count[N]);

    return 0;
}