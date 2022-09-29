#include <bits/stdc++.h>

int main() {
    int T, C;
    scanf("%d%d", &T, &C);
    std::vector<int> chores(C);

    for (int i = 0; i < C; i++) {
        int c;
        scanf("%d", &c);
        chores[i] = c;
    }

    std::sort(chores.begin(), chores.end());

    int sum = 0;
    int count = 0;
    for (int i = 0; i < C; i++) {
        if (sum + chores[i] <= T) {
            sum += chores[i];
            count++;
        } else {
            break;
        }
    }

    printf("%d", count);
    return 0;
}