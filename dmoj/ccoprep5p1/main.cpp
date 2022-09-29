#include <iostream>
#include <deque>

int K, M, N, depths[1000];
bool grid[1000][1000];

int solve() {
    std::fill(depths, depths + N, 0);
    std::deque<std::pair<int, int>> ends;
    int i, ans = 0;

    for (int r = 0; r < M; ++r) {
        ends.clear();
        i = 0;

        for (int c = 0; c < N; ++c) {
            depths[c] = grid[r][c] ? depths[c] + 1 : 0;

            while (!ends.empty() && ends.back().first > depths[c])
                ends.pop_back();

            i = std::min(i, std::max(0, ((int) ends.size()) - 1));

            if (ends.empty() || ends.back().first < depths[c])
                ends.emplace_back(depths[c], c);

            while (i + 1 < ends.size() &&
                   ends[i].first * (c - ends[i].second + 1) <= ends[i + 1].first * (c - ends[i + 1].second + 1))
                ++i;

            ans = std::max(ans, ends[i].first * (c - ends[i].second + 1));
        }
    }

    return ans;
}

int main() {
    std::cin >> K;

    while (K--) {
        std::cin >> M >> N;

        for (int r = 0; r < M; ++r) {
            for (int c = 0; c < N; ++c) {
                char symbol;
                std::cin >> symbol;
                grid[r][c] = symbol == 'F';
            }
        }

        std::cout << solve() * 3 << std::endl;
    }

    return 0;
}