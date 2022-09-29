#include <iostream>
using namespace std;

int N, T, a[15];

int main() {
    scanf("%d", &N);
    scanf("%d", &T);

    for (int i = 0; i < N; i++)
        scanf("%d", a + i);

    int limit = (1 << N), cnt = 0;
    for (int i = 0; i < limit; i++) {
        int sum = 0;
        for (int j = 0; j < N; j++) {
            if (i & (1 << j)) {
                sum += a[j];
            }
        }
        cnt += sum == T;
    }

    printf("%d\n", cnt);

    return 0;
}