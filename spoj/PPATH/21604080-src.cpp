#include <iostream>
#include <vector>
#include <queue>
#define INFINITY 99999999

std::vector<bool> isPrime(10000, true);

void sieve() {
    isPrime[0] = isPrime[1] = false;

    for (int i = 2; i < 10000; i++) {
        if (!isPrime[i]) continue;

        for (int j = i * 2; j < 10000; j += i) {
            isPrime[j] = false;
        }
    }
}

int swap(int num, int dig, int place) {
    int digits[] = {num / 1000, num / 100 % 10, num / 10 % 10, num % 10};
    digits[place] = dig;
    return digits[0] * 1000 + digits[1] * 100 + digits[2] * 10 + digits[3];
}

std::vector<int> getAdj(int num) {
    std::vector<int> adj;

    for (int place = 0; place < 4; place++) {
        for (int digit = 0; digit < 10; digit++) {
            int n = swap(num, digit, place);
            if (n >= 1000 && isPrime[n]) adj.push_back(n);
        }
    }

    return adj;
}

std::vector<int> bfs(int source, int target) {
    std::vector<int> min(10000, INFINITY);
    std::queue<int> q;
    min[source] = 0;
    q.push(source);

    while (!q.empty() && min[target] == INFINITY) {
        int num = q.front(); q.pop();

        for (int adj : getAdj(num)) {
            if (min[adj] == INFINITY) {
                min[adj] = min[num] + 1;
                q.push(adj);
            }
        }
    }

    return min;
}

int main() {
    sieve();

    int N;
    scanf("%d", &N);

    while (N--) {
        int a, b;
        scanf("%d%d", &a, &b);

        std::vector<int> min = bfs(a, b);

        if (min[b] == INFINITY) {
            printf("Impossible\n");
        } else {
            printf("%d\n", min[b]);
        }
    }

    return 0;
}