#include <bits/stdc++.h>

int N;
bool correct = false;
std::vector<std::vector<int>> grid(100, std::vector<int>(100));

void rotate() {
    auto temp = grid;

    int normi = 0, normj = 0;
    for (int j = 0; j < N; j++) {
        for (int i = N - 1; i >= 0; i--) {
            grid[i][j] = temp[normi][normj];
            normj++;
        }
        normi++;
        normj = 0;
    }
}

bool isCorrect() {
    correct = true;

    for (int i = 0; i < N && correct; i++) {
        for (int j = 1; j < N && correct; j++) {
            if (grid[i][j-1] >= grid[i][j]) {
                correct = false;
            }
        }
    }

    for (int j = 0; j < N && correct; j++) {
        for (int i = 1; i < N && correct; i++) {
            if (grid[i-1][j] >= grid[i][j]) {
                correct = false;
            }
        }
    }

    return correct;
}

int main() {
    scanf("%d", &N);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &grid[i][j]);
        }
    }

    for (int i = 0; i < 4 && !correct; i++) {
        if (isCorrect()) {
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < N; j++) {
                    printf("%d ", grid[i][j]);
                }
                printf("\n");
            }
        } else {
            rotate();
        }
    }
}