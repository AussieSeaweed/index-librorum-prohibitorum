#include <iostream>

bool results[31][31][31][31];
int reactions[5][4] = {{2, 1, 0, 2}, {1, 1, 1, 1}, {0, 0, 2, 1}, {0, 3, 0, 0}, {1, 0, 0, 1}};

bool determine(int a, int b, int c, int d) {
    if (a < 0 || b < 0 || c < 0 || d < 0)
        return false;
    else
        return !results[a][b][c][d];
}

int main() {
    for (int a = 0; a < 31; a++)
        for (int b = 0; b < 31; b++)
            for (int c = 0; c < 31; c++)
                for (int d = 0; d < 31; d++)
                    results[a][b][c][d] = false;

    for (int a = 0; a < 31; a++)
        for (int b = 0; b < 31; b++)
            for (int c = 0; c < 31; c++)
                for (int d = 0; d < 31; d++)
                    for (int i = 0; i < 5; i++)
                        if (determine(a - reactions[i][0], b - reactions[i][1], c - reactions[i][2], d - reactions[i][3]))
                            results[a][b][c][d] = true;

    int N;
    int a;
    int b;
    int c;
    int d;

    scanf("%d", &N);

    for (int i = 0; i < N; i++) {
        scanf("%d%d%d%d", &a, &b, &c, &d);
        if (results[a][b][c][d])
            printf("Patrick\n");
        else
            printf("Roland\n");
    }
}