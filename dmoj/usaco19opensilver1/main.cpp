#include <bitset>
#include <algorithm>
#include <iostream>

unsigned int n;
bool grid[1000][1000];
std::size_t rowCount[1000], columnCount[1000], count;

int main() {
    std::cin >> n;

    for (unsigned int r = 0; r < n; ++r) {
        std::string line;
        std::cin >> line;

        for (unsigned int c = 0; c < n; ++c)
            grid[r][c] = line[c] == 'R';
    }

    for (unsigned int i = 0; i < n; ++i) {
        if (grid[i][0])
            for (unsigned int j = 0; j < n; ++j)
                grid[i][j] = !grid[i][j];
        if (grid[0][i])
            for (unsigned int j = 0; j < n; ++j)
                grid[j][i] = !grid[j][i];
    }

    for (unsigned int i = 0; i < n; ++i) {
        for (unsigned int j = 0; j < n; ++j) {
            count += grid[i][j];
            rowCount[i] += grid[i][j];
            columnCount[i] += grid[j][i];
        }
    }

    if (count == (n - 1) * (n - 1))
        std::cout << 1 << ' ' << 1 << std::endl;
    else if (count == n - 1 && std::count(rowCount, rowCount + n, n - 1) == 1)
        std::cout << std::find(rowCount, rowCount + n, n - 1) - rowCount + 1 << ' ' << 1 << std::endl;
    else if (count == n - 1 && std::count(columnCount, columnCount + n, n - 1) == 1)
        std::cout << 1 << ' ' << std::find(columnCount, columnCount + n, n - 1) - columnCount + 1 << std::endl;
    else if (count == 1)
        std::cout << std::find(rowCount, rowCount + n, 1) - rowCount + 1 << ' ' << std::find(columnCount, columnCount + n, 1) - columnCount + 1 << std::endl;
    else
        std::cout << -1 << std::endl;

    return 0;
}