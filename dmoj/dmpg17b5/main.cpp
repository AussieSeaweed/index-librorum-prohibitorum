#include <bits/stdc++.h>

int main() {
    int N;
    int Q;
    scanf("%d", &N);

    std::unordered_map<int, int> wow;
    int maxT = -INFINITY;

    for (int i = 0; i < N; i++) {
        int t, w;
        scanf("%d%d", &t, &w);
        wow[t] = std::max(wow[t], w);
        maxT = std::max(w, maxT);
    }

    std::vector<int> maxWow(maxT + 1, 0);

    for (auto it = wow.begin(); it != wow.end(); it++) {
        maxWow[it->first] = it->second;
    }

    int curMax = 0;
    for (int i = 0; i <= maxT; i++) {
        curMax = std::max(curMax, maxWow[i]);
        maxWow[i] = curMax;
    }

    scanf("%d", &Q);

    while (Q--) {
        int q;
        scanf("%d", &q);
        printf("%d\n", maxWow[std::min(q, maxT)]);
    }

    return 0;
}