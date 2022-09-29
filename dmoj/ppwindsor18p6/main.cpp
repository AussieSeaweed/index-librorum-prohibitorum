#include <bits/stdc++.h>
#include <bits/extc++.h>
#define scan(x) do{while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0');}while(0)
char _;
template<typename T>constexpr const T&_min(const T&x,const T&y) {return x<y?x:y;}
template<typename T>constexpr const T&_max(const T&x,const T&y) {return x<y?y:x;}
template<typename T,typename...Ts> constexpr const T&_min(const T&x,const Ts&...xs) {return _min(x,_min(xs...));}
template<typename T,typename...Ts> constexpr const T&_max(const T&x,const Ts&...xs) {return _max(x,_max(xs...));}
#define min(...) _min(__VA_ARGS__)
#define max(...) _max(__VA_ARGS__)
#define INF 9000000000000000000
#define inf 2000000000
using namespace std;

int M, N;
string grid[1000];
bool visited[1000][1000];
pair<int, int> adj_cells[] {
        {1, 0},
        {-1, 0},
        {0, 1},
        {0, -1}
};
set<int> rooms;

bool valid(int r, int c) {
    return 0 <= r && r < N && 0 <= c && c < M;
}

void dfs(int r, int c) {
    visited[r][c] = true;
    if (isdigit(grid[r][c]))
        rooms.insert(grid[r][c] - '0');

    for (pair<int, int> &adj : adj_cells) {
        int i = r + adj.first;
        int j = c + adj.second;
        if (valid(i, j) && !visited[i][j] && grid[i][j] != '#') {
            dfs(i, j);
        }
    }
}

int main() {
    scan(M);
    scan(N);

    for (int i = 0; i < N; i++)
        cin >> grid[i];

    int r, c;

    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            if (grid[i][j] == '1') {
                r = i, c = j;
                break;
            }

    dfs(r, c);

    for (int id : rooms)
        printf("%d ", id);
    printf("\n");

    return 0;
}