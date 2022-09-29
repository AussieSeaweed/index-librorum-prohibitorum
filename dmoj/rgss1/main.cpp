#include <iostream>
#include <vector>

int main() {
    int A, B, C;
    scanf("%d%d%d", &A, &B, &C);

    std::vector<bool> reachable(C + 1, false);

    int max = 0;
    reachable[0] = true;

    for (int i = 0; i <= C; i++) {
        if (reachable[i]) {
            if (i + A <= C) {
                reachable[i + A] = true;
                max = std::max(max, i + A);
            }

            if (i + B <= C) {
                reachable[i + B] = true;
                max = std::max(max, i + B);
            }
        }
    }

    printf("%d", max);

    return 0;
}