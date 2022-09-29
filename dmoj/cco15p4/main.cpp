#include <iostream>
#include <vector>

using namespace std;

vector<string> grid(2000);
int N, M;

void remove(int r, int c) {
    if (grid[r][c] == 'N') {
        for (int q = r - 1; q >= 0; q--)
            if (grid[q][c] != '.')
                remove(q, c);
    } else if (grid[r][c] == 'S') {
        for (int q = r + 1; q < N; q++)
            if (grid[q][c] != '.')
                remove(q, c);
    } else if (grid[r][c] == 'E') {
        for (int q = c + 1; q < M; q++)
            if (grid[r][q] != '.')
                remove(r, q);
    } else if (grid[r][c] == 'W') {
        for (int q = c - 1; q >= 0; q--)
            if (grid[r][q] != '.')
                remove(r, q);
    }

    grid[r][c] = '.';
    printf("(%d,%d)\n", r, c);
}

int main() {
    scanf("%d%d", &N, &M);
    for (int i = 0; i < N; i++)
        cin >> grid[i];

    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            if (grid[i][j] != '.')
                remove(i, j);

    return 0;
}