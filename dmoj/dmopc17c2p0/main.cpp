#include <bits/stdc++.h>

int sqr_dist(int x1, int y1, int x2, int y2) {
    int dx = x1 - x2;
    int dy = y1 - y2;
    return dx * dx + dy * dy;
}

int main() {
    int x1, y1, x2, y2, xs, ys, D;
    scanf("%d%d%d%d%d%d%d", &x1, &y1, &x2, &y2, &xs, &ys, &D);

    if (sqr_dist(x1, y1, xs, ys) <= D * D || sqr_dist(x2, y2, xs, ys) <= D * D) {
        printf("Yes");
    } else {
        printf("No");
    }
}