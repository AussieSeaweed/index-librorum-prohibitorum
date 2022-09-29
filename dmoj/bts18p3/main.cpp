#include <iostream>
#include <algorithm>
using namespace std;

int N, X;
long long M[100001], width, ans, i;

int main() {
    scanf("%d%d", &N, &X);

    for (int i = 0; i < N; i++)
        scanf("%lld", M + i);

    sort(M, M + N, greater<long long>());

    ans = 0;
    width = 1;
    i = 0;

    while (M[i] == M[i + 1] && i < N) {
        i++;
        width++;
    }

    for (; i < N && X;) {
        if (X >= width) {
            long long iteration = min(X / width, (M[i] - M[i + 1]));
            long long after_value = M[i] - iteration;
            ans += width * (iteration * (after_value + 1 + M[i]) / 2);
            X -= iteration * width;

            M[i] = after_value;
        } else {
            ans += X * M[i];
            X -= X;
        }

        while (M[i] == M[i + 1]) {
            i++;
            width++;
        }
    }

    printf("%lld\n", ans);

    return 0;
}