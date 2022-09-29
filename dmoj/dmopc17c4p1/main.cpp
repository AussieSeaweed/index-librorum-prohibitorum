#include <bits/stdc++.h>

int main() {
    int N, Q;
    scanf("%d%d", &N, &Q);

    std::vector<int> isBlue(N+1, 0);

    while (Q--) {
        int x, y;
        scanf("%d%d", &x, &y);

        isBlue[x]++;
        isBlue[y]--;
    }

    int purples = 0;
    int blues = 0;
    for (int level = 0, i = 0; i < N; i++) {
        level += isBlue[i];

        if (level) {
            blues++;
        } else {
            purples++;
        }
    }

    printf("%d %d", purples, blues);

    return 0;
}