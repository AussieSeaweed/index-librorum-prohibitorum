#include <iostream>
#include <vector>
using namespace std;

vector<int> elems(500001);
vector<int> max_left(500001);
vector<int> max_right(500002);
vector<vector<int>> cnt_left(11, vector<int>(500001));
vector<vector<int>> cnt_right(11, vector<int>(500002));
int N, Q;

int main() {
    scanf("%d%d", &N, &Q);

    for (int i = 1; i <= N; i++)
        scanf("%d", &elems[i]);

    for (int i = 1; i <= N; i++) {
        max_left[i] = max(elems[i], max_left[i - 1]);
        for (int r = 1; r <= 10; r++) {
            cnt_left[r][i] = cnt_left[r][i - 1];
        }
        cnt_left[elems[i]][i]++;
    }

    for (int i = N; i > 0; i--) {
        max_right[i] = max(elems[i], max_right[i + 1]);
        for (int r = 1; r <= 10; r++) {
            cnt_right[r][i] = cnt_right[r][i + 1];
        }
        cnt_right[elems[i]][i]++;
    }

    while (Q--) {
        int left, right;
        scanf("%d%d", &left, &right);
        int value = max(max_left[left - 1], max_right[right + 1]);
        printf("%d %d\n", value, cnt_left[value][left - 1] + cnt_right[value][right + 1]);
    }

    return 0;
}