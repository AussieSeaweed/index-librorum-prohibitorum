#include <iostream>
#include <vector>
#define INFINITY 999999999
using namespace std;

vector<vector<double>> cost(4, vector<double>(10000));
vector<double> price(10000);
int N;

int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; i++) scanf("%lf", &price[i]);

    cost[0][0] = price[0];
    cost[1][0] = INFINITY;
    cost[2][0] = INFINITY;
    cost[3][0] = price[0];

    for (int i = 1; i < N; i++) {
        cost[0][i] = price[i] + cost[3][i - 1];
        cost[1][i] = (price[i] > price[i - 1] ? 0.5 * price[i - 1] + price[i] : 0.5 * price[i] + price[i - 1]) +
                (i - 2 >= 0 ? cost[3][i - 2] : 0);
        if (i >= 2) {
            cost[2][i] = (price[i] + price[i - 1] + price[i - 2]) - min(price[i], min(price[i - 1], price[i - 2])) +
                    (i - 3 >= 0 ? cost[3][i - 3] : 0);
        } else {
            cost[2][i] = INFINITY;
        }
        cost[3][i] = min(cost[0][i], min(cost[1][i], cost[2][i]));
    }

    printf("%.1lf", cost[3][N - 1]);
    return 0;
}