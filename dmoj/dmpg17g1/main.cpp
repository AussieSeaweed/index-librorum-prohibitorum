#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

int candies[4097], mod[2][4096], N, P, modded[4097];
int used[4097], un = 0;

int main() {
    scanf("%d%d", &N, &P);
    for (int i = 1; i <= N; i++)
        scanf("%d", candies + i);
    for (int i = 1; i <= N; i++)
        modded[i] = candies[i] % P;
    memset(mod, -1, sizeof mod);
    mod[0][0] = 0;
    for (int i = 1; i <= N; i++)
        for (int j = 0; j < P; j++)
            if (mod[(i - 1) % 2][j] != -1) {
                mod[i % 2][j] = max(mod[i % 2][j], mod[(i - 1) % 2][j]);
                mod[i % 2][(j + candies[i]) % P] = max(mod[i % 2][(j + candies[i]) % P],
                                                       candies[i] + mod[(i - 1) % 2][j]);
            }
    int soln = mod[N % 2][0];
    printf("%d\n", soln);

    for (int i = N, k = 0; i > 0; i--) {
        for (int j = 0; j < P; j++) {
            mod[(i - 1) % 2][j] = min(mod[i % 2][j], mod[(i - 1) % 2][j]);
            mod[(i - 1) % 2][(j - modded[i] + P) % P] = min(mod[(i - 1) % 2][(j - modded[i] + P) % P],
                                                                   mod[i % 2][j] - candies[i]);
        }
        if (mod[i % 2][k] != mod[(i - 1) % 2][k] && mod[i % 2][k] - candies[i] == mod[(i - 1) % 2][(k - modded[i] + P) % P]) {
            k = (k - modded[i] + P) % P;
            used[un++] = i;
        }
    }

    printf("%d\n", un);
    for (int i = un - 1; i >= 0; i--) printf("%d ", used[i]);
    return 0;
}