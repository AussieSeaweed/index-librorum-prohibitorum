#include <iostream>

int field[1504][1504];
bool visited[1504][1504];
int N, H;

void floodfill(int r, int c) {
    if (0 <= r && r < N && 0 <= c && r < N)
        visited[r][c] = true;
    if (r < N - 1 && !visited[r + 1][c] && abs(field[r + 1][c] - field[r][c]) <= H)
        floodfill(r + 1, c);
    if (0 < r && !visited[r - 1][c] && abs(field[r - 1][c] - field[r][c]) <= H)
        floodfill(r - 1, c);
    if (c < N - 1 && !visited[r][c + 1] && abs(field[r][c + 1] - field[r][c]) <= H)
        floodfill(r, c + 1);
    if (0 < c && !visited[r][c - 1] && abs(field[r][c - 1] - field[r][c]) <= H)
        floodfill(r, c - 1);
}

int main() {
    std::cin >> N;
    std::cin >> H;

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            std::cin >> field[i][j];

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            visited[i][j] = false;

    floodfill(0, 0);

    if (visited[N - 1][N - 1])
        printf("yes\n");
    else
        printf("no\n");
    return 0;
}