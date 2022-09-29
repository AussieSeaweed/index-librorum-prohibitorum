#include <bits/stdc++.h>
#define INF 9999999

int M, Q;
std::vector<int> speeds(101);
std::vector<std::string> names(101);
std::vector<int> r(101, -1);
std::vector<int> last(101, -1);

int get_max(int a, int b) {
    int max = -INF;
    for (int i = a; i <= b; i++) {
        max = std::max(speeds[i], max);
    }
    return max;
}

int min_speed(int n) {
    if (n > Q) return 0;
    if (r[n] != -1) return r[n];

    int min = INF;
    for (int i = 0; i < M; i++) {
        int next = get_max(n, n + i) + min_speed(n + i + 1);
        if (next < min) {
            min = next;
            last[n] = n+i;
        }
    }

    r[n] = min;
    return min;
}

int main() {
    scanf("%d%d", &M, &Q);
    for (int i = 1; i <= Q; i++) {
        std::string name; int speed;
        std::cin >> name;
        scanf("%d", &speed);

        speeds[i] = speed;
        names[i] = name;
    }

    printf("Total Time: %d\n", min_speed(0));
    for (int i = 1; i <= Q; i = last[i] + 1) {
        for (int j = i; j <= last[i]; j++)
            std::cout << names[j] << " ";
        printf("\n");
    }

    return 0;
}