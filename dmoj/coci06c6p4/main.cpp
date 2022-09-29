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

int R, C, N;
char grid[30000][35];
struct Strip {
    int c[30000];
    int r = 0;

    void update() {
        while (true) {
            if (r >= 0 && grid[r][c[r]] != '.') {
                r--;
            } else if (r == R - 1 || grid[r + 1][c[r]] == 'X') {
                break;
            } else if (grid[r + 1][c[r]] == 'O' && c[r] && grid[r][c[r] - 1] == '.' && grid[r + 1][c[r] - 1] == '.') {
                c[r + 1] = c[r] - 1;
                r++;
            } else if (grid[r + 1][c[r]] == 'O' && c[r] < C - 1 && grid[r][c[r] + 1] == '.' && grid[r + 1][c[r] + 1] == '.') {
                c[r + 1] = c[r] + 1;
                r++;
            } else if (grid[r + 1][c[r]] == '.') {
                c[r + 1] = c[r];
                r++;
            } else {
                break;
            }
        }
    }

    void place() {
        grid[r][c[r]] = 'O';
    }
} strips[30];

int main() {
    scan(R);
    scan(C);

    for (int r = 0; r < R; r++)
        scanf("%s", grid[r]);

    for (int c = 0; c < C; c++) {
        strips[c].c[0] = c;
        strips[c].update();
    }

    scan(N);

    while (N--) {
        int c;
        scan(c);
        --c;
        strips[c].place();
        for (c = 0; c < C; c++)
            strips[c].update();
    }

    for (int r = 0; r < R; r++)
        printf("%s\n", grid[r]);

    return 0;
}