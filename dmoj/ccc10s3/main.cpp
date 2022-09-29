#include <iostream>
#include <algorithm>

int H, K, h[2000];

bool possible(int length) {
    for (int i = 0; i < H; i++) {
        int prev = h[i];
        int num = 1;

        for (int j = i + 1; j < H + i && num != K + 1; j++) {
            if (h[j] - prev > length) {
                num++;
                prev = h[j];
            }
        }

        if (num <= K) return true;
    }

    return false;
}

int main() {
    scanf("%d", &H);

    for (int i = 0; i < H; i++)
        scanf("%d", h + i);

    std::sort(h, h + H);

    for (int i = H; i < 2 * H; i++)
        h[i] = h[i - H] + 1000000;

    scanf("%d", &K);

    int lo = 0, hi = 1000000;

    while (lo <= hi) {
        int mid = (lo + hi) / 2;

        if (possible(mid)) {
            hi = mid - 1;
        } else {
            lo = mid + 1;
        }
    }

    printf("%d\n", lo / 2 + lo % 2);

    return 0;
}