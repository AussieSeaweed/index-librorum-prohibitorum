#include <iostream>

int main() {
    int N;
    scanf("%d", &N);
    int numbers[200001];
    numbers[N] = 1000001;

    for (int i = 0; i < N; i++)
        scanf("%d", numbers + i);

    bool used = false;
    int wildcard = -1;
    int prev = 1;

    for (int i = 0; i < N; i++) {
        if (!numbers[i]) {
            if (!used && numbers[i + 1]) {
                used = true;
                wildcard = numbers[i + 1];
            }

            if (used && wildcard < prev) {
                printf("NO\n");
                return 0;
            }

            numbers[i] = wildcard;
        } else {
            if (!numbers[i + 1]) {
                prev = numbers[i];
            } else if (numbers[i] > numbers[i + 1]) {
                printf("NO\n");
                return 0;
            }
        }
    }

    printf("YES\n");

    return 0;
}