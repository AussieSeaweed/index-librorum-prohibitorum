#include <iostream>
#include <vector>
#include <map>

using namespace std;

vector<vector<int>> ids(1000, vector<int>(1000));
vector<vector<bool>> visited(1000, vector<bool>(1000, false));
vector<vector<bool>> tempVisited(1000, vector<bool>(1000, false));
vector<pair<int, int>> lst;
vector<string> grid(1000);
map<char, pair<int, int>> dir {
        {'S', {1, 0}},
        {'N', {-1, 0}},
        {'E', {0, 1}},
        {'W', {0, -1}}
};
int count = 0;
int n, m;

void dfs(int r, int c) {
    tempVisited[r][c] = true;
    lst.emplace_back(r, c);

    pair<int, int> direction = dir[grid[r][c]];
    int nr = direction.first + r;
    int nc = direction.second + c;
    if (tempVisited[nr][nc])
        count++;
    else if (!visited[nr][nc])
        dfs(nr, nc);

}

int main() {
    scanf("%d%d", &n, &m);

    for (int i = 0; i < n; i++)
        cin >> grid[i];

    for (int r = 0; r < n; r++)
        for (int c = 0; c < m; c++)
            if (!visited[r][c]) {
                dfs(r, c);
                for (pair<int, int> p : lst) {
                    visited[p.first][p.second] = true;
                    tempVisited[p.first][p.second] = false;
                }
                lst.clear();
            }

    printf("%d", count);

    return 0;
}