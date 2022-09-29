#include <bits/stdc++.h>

std::vector<int> wood(2001, 0);
std::vector<int> fence(4001, 0);
int N;

int main() {
    scanf("%d", &N);
    for (int len, i = 0; i < N; i++) {
        scanf("%d", &len);
        wood[len]++;
    }

    for (int i = 1; i <= 2000; i++) {
        if (wood[i]) {
            for (int j = i; j <= 2000; j++)
                if (i == j) fence[i + j] += wood[i] >> 1;
                else if (wood[j]) fence[i + j] += std::min(wood[i], wood[j]);
        }
    }

    int length = -1, num = -1;
    for (int i = 1; i <= 4000; i++) {
        if (fence[i] > length) {
            length = fence[i];
            num = 1;
        } else if (fence[i] == length)
            num++;
    }

    printf("%d %d\n", length, num);
}