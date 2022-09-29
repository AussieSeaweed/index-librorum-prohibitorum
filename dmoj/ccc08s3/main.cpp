#include <bits/stdc++.h>
#define INF 9999999

int r, c;
std::vector<std::string> maze;
std::vector<std::vector<int>> min;

void dfs(int p, int q, int step) {
    if (0 <= p && p < r && 0 <= q && q < c && min[p][q] > step && maze[p][q] != '*') {
        min[p][q] = step;

        bool up = false;
        bool down = false;
        bool right = false;
        bool left = false;

        if (maze[p][q] == '+') {
            up = true;
            down = true;
            right = true;
            left = true;
        } else if (maze[p][q] == '-') {
            right = true;
            left = true;
        } else if (maze[p][q] == '|') {
            up = true;
            down = true;
        }

        if (up) dfs(p - 1, q, step + 1);
        if (down) dfs(p + 1, q, step + 1);
        if (right) dfs(p, q + 1, step + 1);
        if (left) dfs(p, q - 1, step + 1);
    }
}

int main() {
    int t;
    scanf("%d", &t);

    while (t--) {
        scanf("%d%d", &r, &c);

        maze = std::vector<std::string>(r);
        min = std::vector<std::vector<int>>(r, std::vector<int>(c, INF));

        for (int i = 0; i < r; i++) {
            std::cin >> maze[i];
        }

        dfs(0, 0, 1);

        printf("%d\n", min[r-1][c-1] == INF ? -1 : min[r-1][c-1]);
    }
}