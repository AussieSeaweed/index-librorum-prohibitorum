#include <bits/stdc++.h>
#define scan(x) do{while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0');}while(0)
char _;
#define INF 9000000000000000000
#define inf 2000000000
using namespace std;

int grid[9][9];
bool contains_in_quad[3][3][10], contains_in_row[9][10], contains_in_col[9][10];
unordered_set<int> possible[9][9];
vector<int> digits {1, 2, 3, 4, 5, 6, 7, 8, 9};


void pick(int i, int j, int value) {
    grid[i][j] = value;
    possible[i][j].clear();
    contains_in_row[i][grid[i][j]] = true;
    contains_in_col[j][grid[i][j]] = true;
    contains_in_quad[i / 3][j / 3][grid[i][j]] = true;
}

int main() {
    for (int i = 0; i < 9; i++) {
        fill(grid[i], grid[i] + 9, -1);
        string str;
        cin >> str;
        for (int j = 0; j < 9; j++) {
            if (str[j] == '.') {
                possible[i][j].insert(digits.begin(), digits.end());
            } else {
                possible[i][j].insert(str[j] - '0');
            }
        }
    }

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (possible[i][j].size() == 1) {
                pick(i, j, *possible[i][j].begin());
            }
        }
    }

    bool modified = true;

    while (modified) {
        modified = false;

        for (int k = 1; k <= 9; k++) {
            for (int r = 0, i = 0; r < 9; r += 3, i = r / 3) {
                for (int c = 0, j = 0; c < 9; c += 3, j = c / 3) {
                    if (!contains_in_quad[i][j][k]) {
                        int count = 0, a = -1, b = -1;

                        for (int p = r; p < r + 3; p++) {
                            for (int q = c; q < c + 3; q++) {
                                if (grid[p][q] == -1 && !contains_in_row[p][k] && !contains_in_col[q][k]) {
                                    count++;
                                    a = p;
                                    b = q;
                                }
                            }
                        }

                        if (count == 1) {
                            pick(a, b, k);
                            modified = true;
                        } else if (count == 0) {
                            printf("ERROR\n");
                            return 0;
                        }
                    }
                }
            }
        }
    }

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            printf("%c", grid[i][j] == -1 ? '.' : grid[i][j] + '0');
        }
        printf("\n");
    }

    return 0;
}