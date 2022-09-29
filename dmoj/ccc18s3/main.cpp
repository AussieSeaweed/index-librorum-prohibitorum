#include <bits/stdc++.h>
#define INF 9999999

int N, M;
std::vector<std::vector<char>> factory(101, std::vector<char>(101));
std::vector<std::vector<int>> min(101, std::vector<int>(101, INF));
std::vector<std::vector<bool>> spotted(101, std::vector<bool>(101, false));

void fill(int i, int j) {
    for (int q = j-1; q >= 0; q--) {
        if (factory[i][q] == 'W') break;
        else if (factory[i][q] == '.' || factory[i][q] == 'S') spotted[i][q] = true;
    }

    for (int q = j+1; q < M; q++) {
        if (factory[i][q] == 'W') break;
        else if (factory[i][q] == '.' || factory[i][q] == 'S') spotted[i][q] = true;
    }

    for (int p = i-1; p >= 0; p--) {
        if (factory[p][j] == 'W') break;
        else if (factory[p][j] == '.' || factory[p][j] == 'S') spotted[p][j] = true;
    }

    for (int p = i+1; p < N; p++) {
        if (factory[p][j] == 'W') break;
        else if (factory[p][j] == '.' || factory[p][j] == 'S') spotted[p][j] = true;
    }
}

void dfs(int i, int j, int step) {
    if (i < 0 || i >= N || 0 > j || j >= M || factory[i][j] == 'C' || factory[i][j] == 'W' || spotted[i][j]) return;

    min[i][j] = std::min(min[i][j], step);

    int newStep = factory[i][j] == '.' ? step + 1 : step;

    bool up = false, down = false, right = false, left = false;

    if (factory[i][j] == 'L') left = true;
    else if (factory[i][j] == 'R') right = true;
    else if (factory[i][j] == 'U') up = true;
    else if (factory[i][j] == 'D') down = true;
    else if (factory[i][j] == '.' || factory[i][j] == 'S') up = true, down = true, right = true, left = true;

    if (up) {
        if (min[i-1][j] > newStep)
            dfs(i-1, j, newStep);
    }

    if (down) {
        if (min[i+1][j] > newStep)
            dfs(i+1, j, newStep);
    }

    if (right) {
        if (min[i][j+1] > newStep)
            dfs(i, j+1, newStep);
    }

    if (left) {
        if (min[i][j-1] > newStep)
            dfs(i, j-1, newStep);
    }
}

int main() {
    scanf("%d%d", &N, &M);

    int starti, startj;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            char c;
            std::cin >> c;
            if (c == 'S') starti = i, startj = j;
            factory[i][j] = c;
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (factory[i][j] == 'C')
                fill(i, j);
        }
    }

    dfs(starti, startj, 1);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (factory[i][j] == '.') {
                printf("%d\n", min[i][j] == INF ? -1 : min[i][j]);
            }
        }
    }
}