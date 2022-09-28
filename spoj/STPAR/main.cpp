#include <bits/stdc++.h>

int main() {
    while (true) {
        int N;
        scanf("%d", &N);

        if (!N) break;

        std::queue<int> normal;
        std::stack<int> alley;

        for (int i = 0; i < N; i++) {
            int t;
            scanf("%d", &t);
            normal.push(t);
        }

        bool possible = true;
        int req = 1;
        while (!normal.empty() || !alley.empty()) {
            if (normal.empty() && alley.top() != req) {
                possible = false;
                break;
            }

            if (!normal.empty() && normal.front() == req) {
                normal.pop();
                req++;
            } else if (!alley.empty() && alley.top() == req) {
                alley.pop();
                req++;
            } else {
                alley.push(normal.front());
                normal.pop();
            }
        }

        printf(possible ? "yes\n" : "no\n");
    }
}