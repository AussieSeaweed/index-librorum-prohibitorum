#include <iostream>

char grid[2000][2000];
int sums[2000][2000];
int N;

int main() {
    scanf("%d", &N);

    for (int i = 0; i < N; i++)
        scanf("%s", grid[i]);

    for (int r = 0; r < N; r++)
        for (int c = 0; c < N; c++)
            sums[r][c] = 0;

    for (int r = N - 1; r >= 0; r--)
        for (int c = 0; c < N; c++) {
            if (grid[r][c] == '#') {
                sums[r][c]++;
                if (r < N - 1 && 0 < c && c < N - 1 && grid[r + 1][c - 1] == '#' && grid[r + 1][c] == '#' && grid[r + 1][c + 1] == '#')
                    sums[r][c] += std::min(std::min(sums[r + 1][c - 1], sums[r + 1][c + 1]), sums[r + 1][c]);
            }
        }

    int sum = 0;

    for (int r = 0; r < N; r++)
        for (int c = 0; c < N; c++)
            sum += sums[r][c];

    printf("%d", sum);
    return 0;
}