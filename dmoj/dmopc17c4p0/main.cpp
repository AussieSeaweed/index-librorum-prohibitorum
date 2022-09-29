#include <bits/stdc++.h>

int sqrdist(std::pair<int, int> a, std::pair<int, int> b) {
    int dx = a.first - b.first;
    int dy = a.second - b.second;
    return dx * dx + dy * dy;
}

int main() {
    int x1, y1, x2, y2, x3, y3;
    scanf("%d%d%d%d%d%d", &x1, &y1, &x2, &y2, &x3, &y3);

    std::vector<std::pair<int ,int>> pts = {{x1, y1}, {x2, y2}, {x3, y3}};

    int min = INFINITY;
    for (int i = 0; i < 3; i++) {
        for (int j = i+1; j < 3; j++) {
            min = std::min(min, sqrdist(pts[i], pts[j]));
        }
    }

    printf("%d", min);

    return 0;
}