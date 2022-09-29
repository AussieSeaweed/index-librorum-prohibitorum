#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> layers(2000);
vector<int> heights(2000);
int N, K;

int main() {
    scanf("%d%d", &N, &K);
    for (int i = 0; i < N; i++)
        scanf("%d", &layers[i]);

    sort(layers.begin(), layers.begin() + N);

    int ans = 1;
    heights[0] = 1;

    for (int i = 1; i < N; i++) {
        heights[i] = 1;
        int most = 0;
        for (int j = i - 1; j >= 0; j--) {
            if (layers[i] - layers[j] >= K) {
                most = max(most, heights[j]);
            }
        }
        heights[i] += most;
        ans = max(ans, heights[i]);
    }

    printf("%d", ans);
    return 0;
}