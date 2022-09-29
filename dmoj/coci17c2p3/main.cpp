#include <iostream>
#include <vector>

int n, C[500000], F[500001];
std::vector<int> lengths[2][500000];

int main() {
    std::cin >> n;

    for (int i = 0; i < n; ++i) {
        std::cin >> C[i];
        F[i + 1] = F[i] + (--C[i] == i);
    }

    for (int i = 0; i < n; ++i) {
        int length = std::abs(C[i] - i) + 1, mid = (i + C[i] + 1) / 2;
        lengths[length & 1][mid].push_back(length);
    }

    int count = 0, begin = 0, end = 1;

    for (int i = 0; i < n; ++i) {
        std::sort(lengths[0][i].begin(), lengths[0][i].end());

        for (int j = 0; j < lengths[0][i].size(); ++j) {
            int u = i - lengths[0][i][j] / 2, v = i + lengths[0][i][j] / 2, m = j + 1 - F[v] + F[u];

            if (m > count) {
                count = m;
                begin = u;
                end = v;
            }
        }

        std::sort(lengths[1][i].begin(), lengths[1][i].end());


        for (int j = 0; j < lengths[1][i].size(); ++j) {
            int u = i - lengths[1][i][j] / 2, v = i + lengths[1][i][j] / 2 + 1, m = j + 1 - F[v] + F[u];

            if (m > count) {
                count = m;
                begin = u;
                end = v;
            }
        }
    }

    std::cout << C[begin] + 1 << ' ' << C[end - 1] + 1 << std::endl;

    return 0;
}