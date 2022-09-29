#include <iostream>
#include <vector>
#define INFINITY 9999999999999999ll
using namespace std;

vector<vector<long long>> density(1000, vector<long long>(1000));
vector<vector<long long>> best(1000, vector<long long>(1000, INFINITY));
int L, D;

int main() {
    scanf("%d%d", &L, &D);

    for (int i = 0; i < D; i++)
         for (int j = 0; j < L; j++)
             scanf("%lld", &density[i][j]);

    best[0][0] = density[0][0];

    for (int l = 1; l < L; l++) {
        best[0][l] = best[0][l - 1] + density[0][l];
    }

    for (int d = 1; d < D; d++) {
        best[d][0] = density[d][0] + best[d - 1][0];
        for (int l = 1; l < L; l++) {
            best[d][l] = min(best[d][l], min(best[d][l - 1], best[d - 1][l]) + density[d][l]);
        }

        best[d][L - 1] = min(best[d][L - 1], density[d][L - 1] + best[d - 1][L - 1]);
        for (int l = L - 2; l >= 0; l--) {
            best[d][l] = min(best[d][l], min(best[d][l + 1], best[d - 1][l]) + density[d][l]);
        }
    }

    int tl, td;
    scanf("%d%d", &tl, &td);
    printf("%lld", best[td][tl]);
    return 0;
}