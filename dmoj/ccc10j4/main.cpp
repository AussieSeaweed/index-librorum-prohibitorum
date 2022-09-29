#include <iostream>
#include <vector>

int main() {
    while (true) {
        int N;
        scanf("%d", &N);

        if (!N) break;

        std::vector<int> temp(N);

        for (int i = 0; i < N; i++) {
            scanf("%d", &temp[i]);
        }

        int l;
        for (l = 1; l < N; l++) {
            std::vector<int> pattern(l);
            for (int i = 0; i < l; i++)
                pattern[i] = temp[i + 1] - temp[i];

            int count = 0;
            bool flag = false;
            for (int i = l; i < N - 1 && !flag; i++, count %= l) {
                if (temp[i + 1] - temp[i] != pattern[count++]) flag = true;
            }

            if (!flag) break;
        }

        printf("%d\n", N == 1 ? 0 : l);
    }

    return 0;
}