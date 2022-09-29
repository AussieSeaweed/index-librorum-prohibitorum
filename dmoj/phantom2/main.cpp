#include <iostream>
#include <vector>

std::vector<bool> sieve(1000001, true);

void build_sieve(int N) {
    sieve[0] = false;
    sieve[1] = false;

    for (int i = 2; i <= N; i++) {
        if (sieve[i]) {
            for (int j = i * 2; j <= N; j += i)
                sieve[j] = false;
        }
    }
}

int main() {
    build_sieve(1000000);

    int N;
    scanf("%d", &N);

    while (N--) {
        int a, b;
        scanf("%d%d", &a, &b);

        int counter = 0;

        for (; a < b; a++)
            if (sieve[a])
                counter++;

        printf("%d\n", counter);
    }

    return 0;
}