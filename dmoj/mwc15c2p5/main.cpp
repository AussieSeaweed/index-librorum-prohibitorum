#include <iostream>
#include <vector>
using namespace std;

vector<vector<long long>> food(4, vector<long long>(100002, 0));
int N, K, J;

int main() {
    scanf("%d%d%d", &N, &K, &J);

    while (J--) {
        int i, j, T;
        long long I;
        scanf("%d%d%lld%d", &i, &j, &I, &T);
        food[T][i] += I;
        food[T][j + 1] -= I;
    }

    for (int i = 1; i <= N; i++) {
        food[1][i] += food[1][i - 1];
        food[2][i] += food[2][i - 1];
        food[3][i] += food[3][i - 1];
    }

    int ans1 = 0, ans2 = 0, ans3 = 0;
    for (int i = 1; i <= N; i++) {
        ans1 += food[1][i] < K;
        ans2 += food[2][i] < K;
        ans3 += food[3][i] < K;
    }

    printf("%d\n%d\n%d", ans1, ans2, ans3);

    return 0;
}