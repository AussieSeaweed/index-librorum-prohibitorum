#include <iostream>
#include <vector>
#include <algorithm>

int R, C;
std::vector<std::string> cage(35);
std::vector<std::vector<int>> ids(35, std::vector<int>(50, -1));

bool isValid(int r, int c) {
    return 0 <= r && r < R && 0 <= c && c < C;
}

void floodFill(int r, int c, int id) {
    if (isValid(r, c) && !ids[r][c]) {
        ids[r][c] = id;
        floodFill(r + 1, c, id);
        floodFill(r, c + 1, id);
        floodFill(r - 1, c, id);
        floodFill(r, c - 1, id);
    }
}

int main() {
    scanf("%d%d", &R, &C);

    for (int i = 0; i < R; i++)
        std::cin >> cage[i];

    for (int r = 0; r < R; r++)
        for (int c = 0; c < C; c++) {
            if (cage[r][c] == '#')
                ids[r][c] = -1;
            else
                ids[r][c] = 0;
        }

    int id = 1;

    for (int r = 0; r < R; r++)
        for (int c = 0; c < C; c++)
            if (!ids[r][c] && cage[r][c] != '#')
                floodFill(r, c, id++);

    std::vector<bool> containsM(id, false);

    for (int r = 0; r < R; r++)
        for (int c = 0; c < C; c++)
            if (cage[r][c] == 'M')
                containsM[ids[r][c]] = true;

    int ans = 0;

    for (int i = 1; i < id; i++)
        if (containsM[i]) ans++;

    printf("%d\n", ans);

    return 0;
}