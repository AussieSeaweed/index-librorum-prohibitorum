#include <iostream>
#include <vector>
using namespace std;

vector<int> elems(100);
vector<vector<int>> memo(100, vector<int>(100, -1));
int N, TOTAL, cnt;

int solve(int i, int j) {
    if (memo[i][j] != -1) return memo[i][j];

    if (i == j) return memo[i][j] = elems[i] % 2;
    if ((i - 1 + N) % N == j) return memo[i][j] = elems[i] % 2 || elems[j] % 2;

    return memo[i][j] = max(
            elems[i] % 2 + min(
                    solve((i - 1 + N) % N, (j + 1) % N),
                    solve((i - 2 + N) % N, j)),
            elems[j] % 2 + min(
                    solve((i - 1 + N) % N, (j + 1) % N),
                    solve(i, (j + 2) % N))
    );
}

int main() {
    scanf("%d" ,&N);
    for (int i = 0; i < N; i++) scanf("%d", &elems[i]);
    TOTAL = 0, cnt = 0;
    for (int i = 0; i < N; i++) TOTAL += elems[i] % 2;
    for (int i = 0; i < N; i++) cnt += (TOTAL / 2) < elems[i] % 2 + min(solve((i - 2 + N) % N, (i + 1) % N), solve((i - 1 + N) % N, (i + 2) % N));
    printf("%d", cnt);
    return 0;
}