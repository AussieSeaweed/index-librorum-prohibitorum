#include <bits/stdc++.h>

int main() {
    int N, D;
    scanf("%d%d", &N, &D);
    std::vector<int> pos(N+1);

    for (int i = 1; i <= N; i++) {
        scanf("%d", &pos[i]);
    }

    bool goRight = false;
    bool goLeft = false;
    int minStart = INFINITY;
    int maxStart = -INFINITY;
    int minDest = INFINITY;
    int maxDest = -INFINITY;

    int s, d;
    for (int i = 0; i < D; i++) {
        scanf("%d%d", &s, &d);

        if (pos[s] < pos[d]) goRight = true;
        else if (pos[s] > pos[d]) goLeft = true;

        minStart = std::min(minStart, pos[s]);
        maxStart = std::max(maxStart, pos[s]);
        minDest = std::min(minDest, pos[d]);
        maxDest = std::max(maxDest, pos[d]);
    }

    int ans;
    if (!goRight && !goLeft) {
        ans = 0;
    } else if (goRight && goLeft) {
        ans = std::min((std::max(maxDest, maxStart) - minStart) + (std::max(maxDest, maxStart) - minDest), (maxStart - std::min(minDest, minStart)) + (maxDest - std::min(minDest, minStart)));
    } else if (goRight) {
        ans = maxDest - minStart;
    } else {
        ans = maxStart - minDest;
    }

    printf("%d", ans);
    return 0;
}