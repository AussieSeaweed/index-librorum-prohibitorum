#include <iostream>
#include <vector>



int main() {
int _ = 5;
while (_--) {
    std::vector<std::string> grid;
    std::vector<std::vector<int>> money(8, std::vector<int>(8, 0));
    std::vector<std::vector<int>> max(8, std::vector<int>(8, -1));

    for (int i = 0; i < 8; i++) {
        std::string str;
        std::cin >> str;
        grid.push_back(str);
    }

    std::string _str;
    std::cin >> _str;

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (grid[i][j] == '#') continue;
            else if (grid[i][j] == '.') money[i][j] = 0;
            else money[i][j] = grid[i][j] - '0';
        }
    }

    max[7][0] = money[7][0];

    for (int i = 1; i < 8; i++) {
        if (grid[7][i] == '#') break;
        max[7][i] = max[7][i - 1] + money[7][i];
    }

    for (int i = 6; i >= 0; i--) {
        for (int j = 0; j < 8; j++) {
            if (max[i + 1][j] == -1 || grid[i][j] == '#') continue;
            max[i][j] = std::max(max[i + 1][j] + money[i][j], max[i][j]);

            for (int k = j + 1; k < 8; k++) {
                if (grid[i][k] == '#') break;
                max[i][k] = std::max(max[i][k - 1] + money[i][k], max[i][k]);
            }
        }
    }

    printf("%d\n", max[0][7]);
}

    return 0;
}