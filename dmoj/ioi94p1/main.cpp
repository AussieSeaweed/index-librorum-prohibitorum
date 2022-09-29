#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> triangle;
int N;

int main() {
    scanf("%d", &N);

    for (int i = 0; i < N; i++) {
        triangle.emplace_back(i + 1);
        for (int j = 0; j <= i; j++) {
            scanf("%d", &triangle[i][j]);
        }
    }

    for (int i = N - 2; i >= 0; i--) {
        for (int j = 0; j <= i; j++) {
            triangle[i][j] += max(triangle[i + 1][j], triangle[i + 1][j + 1]);
        }
    }

    printf("%d", triangle[0][0]);

    return 0;
}