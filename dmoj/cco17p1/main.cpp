#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int K;
vector<int> num;
vector<pair<int, int>> edges;

int main() {
    scanf("%d", &K);

    if (K == 0) {
        printf("2 1\n1 2\n");
        return 0;
    }

    num.push_back(0);

    for (int i = 1; i <= 5000; i++) {
        num.push_back((i * (i - 1)) / 2);
    }

    int V = 0, E = 0;

    while (K) {
        auto it = --upper_bound(num.begin(), num.end(), K);

        if (V != 0) {
            E++;
            edges.emplace_back(V, V + 1);
        }

        for (int i = 0; i < it - num.begin(); i++) {
            edges.emplace_back(i + V + 1, (i + 1) % (it - num.begin()) + V + 1);
        }

        V += it - num.begin();
        E += it - num.begin();
        K -= *it;
    }

    printf("%d %d\n", V, E);

    for (pair<int, int> edge : edges) {
        printf("%d %d\n", edge.first, edge.second);
    }
}