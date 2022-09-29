#include <bits/stdc++.h>

int main() {
    for (int _ = 0; _ < 10; _++) {
        int N;
        scanf("%d", &N);

        int cost = 0;

        std::deque<int> carts(N);

        for (int i = 0; i < N; i++) {
            scanf("%d", &carts[i]);
        }

        for (int i = N; i > 1; i--) {
            int current_index;
            int larger_index;

            for (int j = 0; j < N; j++) {
                if (carts[j] == i)
                    larger_index = j;
                else if (carts[j] == i - 1)
                    current_index = j;
            }

            if (current_index > larger_index) {
                cost += current_index;
                carts.erase(carts.begin() + current_index);
                carts.push_front(i - 1);
            }
        }

        printf("%d\n", cost);
    }
}