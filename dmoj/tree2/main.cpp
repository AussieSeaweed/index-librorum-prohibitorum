#include <iostream>
#include <queue>
#include <climits>

int R, C, weights[10][10], rs, cs, rt, ct, dists[10][10], counts[10][10];
std::pair<int, int> offsets[4]{{1,  0},
                               {0,  1},
                               {-1, 0},
                               {0,  -1}};

void findMax() {
    for (int r = 0; r < R; ++r)
        for (int c = 0; c < C; ++c)
            if (weights[r][c] > weights[rt][ct]
                || (weights[r][c] == weights[rt][ct] &&
                    std::abs(r - rs) + std::abs(c - cs) < std::abs(rt - rs) + std::abs(ct - cs)))
                rt = r, ct = c;
}

int solve() {
    for (int r = 0; r < R; ++r)
        for (int c = 0; c < C; ++c)
            dists[r][c] = counts[r][c] = INT_MAX;

    std::queue<std::pair<int, int>> queue;
    dists[rs][cs] = counts[rs][cs] = 0;
    queue.emplace(rs, cs);

    while (!queue.empty()) {
        auto[r, c] = queue.front();
        queue.pop();

        for (auto[dr, dc]: offsets) {
            int nr = r + dr, nc = c + dc;

            if (nr < 0 || nr >= R || nc < 0 || nc >= C)
                continue;

            if (dists[nr][nc] > dists[r][c] + weights[nr][nc]
                || (dists[nr][nc] == dists[r][c] + weights[nr][nc] &&
                    counts[nr][nc] > counts[r][c] + (weights[nr][nc] > 0))) {
                dists[nr][nc] = dists[r][c] + weights[nr][nc];
                counts[nr][nc] = counts[r][c] + (weights[nr][nc] > 0);
                queue.emplace(nr, nc);
            }
        }
    }

    return counts[rt][ct] - 1;
}

int main() {
    std::cin >> R >> C;

    for (int r = 0; r < R; ++r) {
        for (int c = 0; c < C; ++c) {
            char ch;
            std::cin >> ch;

            if (isdigit(ch))
                weights[r][c] = ch - '0';
            else {
                weights[r][c] = 0;

                if (ch == 'X')
                    rs = r, cs = c;
            }
        }
    }

    findMax();

    std::cout << solve() << std::endl;

    return 0;
}