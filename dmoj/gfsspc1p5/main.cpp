#include <iostream>
#include <vector>
#include <algorithm>
#define INFINITY 99999999
using namespace std;

int N, T;
vector<int> coords;

int main() {
    scanf("%d%d", &N, &T);
    for (int i = 0; i < N; i++) {
        int ui;
        scanf("%d", &ui);
        coords.push_back(ui);
    }
    int ans = INFINITY;

    sort(coords.begin(), coords.end());

    for (int i = 0; i <= N - T; i++) {
        int a = coords[i];
        int b = coords[i + T - 1];
        ans = min(ans, min(abs(a), abs(b)) + (b - a));
    }

    printf("%d", ans);

    return 0;
}