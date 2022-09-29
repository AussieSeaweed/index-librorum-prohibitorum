#include <iostream>
#include <stack>
#include <unordered_set>

struct PairHash {
    template<typename T1, typename T2>
    bool operator()(const std::pair<T1, T2> &pair) const {
        return std::hash<T1>{}(pair.first) ^ std::hash<T2>{}(pair.second);
    }
};

unsigned int n, i, h, m, H[10000], begins[10000], ends[10000];
std::unordered_set<std::pair<unsigned int, unsigned int>, PairHash> recordings;

int main() {
    std::cin >> n >> i >> h >> m;

    for (unsigned int j = 0; j < m; ++j) {
        unsigned int u, v;
        std::cin >> u >> v;
        --u, --v;

        if (!recordings.count(std::make_pair(u, v))) {
            recordings.emplace(u, v);
            ++begins[std::min(u, v)];
            ++ends[std::max(u, v)];
        }
    }

    for (unsigned int j = 0, c = 0; j < n; ++j) {
        c -= ends[j];
        H[j] = h - c;
        c += begins[j];
    }

    for (unsigned int j = 0; j < n; ++j)
        std::cout << H[j] << std::endl;

    return 0;
}