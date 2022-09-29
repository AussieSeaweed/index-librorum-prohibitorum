#include <iostream>
#include <unordered_map>
#include <algorithm>

int N, T;
std::string n[10];
std::unordered_map<std::string, int> cost;

int main() {
    scanf("%d%d", &N, &T);
    int _ = N;
    while (_--) {
        std::cin >> n[_];
        std::cin >> cost[n[_]];
    }
    std::sort(n, n + N);
    for (int i = 0; i < N; i++)
        for (int j = i + 1; j < N; j++)
            for (int k = j + 1; k < N; k++)
                if (cost[n[i]] + cost[n[j]] + cost[n[k]] <= T)
                    std::cout << n[i] << " " << n[j] << " " << n[k] << "\n";
    return 0;
}