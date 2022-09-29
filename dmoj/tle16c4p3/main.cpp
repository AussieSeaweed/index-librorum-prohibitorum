#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

vector<vector<int>> c(9, vector<int>(9, false));
int N;

int main() {
    scanf("%d", &N);

    for (int i = 0; i < N; i++) {
        int v, w;
        scanf("%d%d", &v, &w);
        c[v][w] = true;
        c[w][v] = true;
    }

    int vertices[] = {1, 2, 3, 4, 5, 6, 7, 8};
    bool flag = false;

    do {
        flag = c[vertices[0]][vertices[1]] && c[vertices[0]][vertices[2]] && c[vertices[1]][vertices[3]] && c[vertices[3]][vertices[2]] && \
        c[vertices[0]][vertices[6]] && c[vertices[1]][vertices[7]] && c[vertices[3]][vertices[4]] && c[vertices[2]][vertices[5]] && \
        c[vertices[5]][vertices[4]] && c[vertices[6]][vertices[5]] && c[vertices[6]][vertices[7]] && c[vertices[4]][vertices[7]];
    } while (!flag && next_permutation(vertices, vertices + 8));

    if (flag) printf("Ja\n");
    else printf("Nej\n");
}