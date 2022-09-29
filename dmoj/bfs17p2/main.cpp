#include <bits/stdc++.h>

int main() {
    int N;
    scanf("%d", &N);

    std::map<std::string, int> markers = {{"red",0}, {"orange",0}, {"yellow",0}, {"green",0}, {"blue",0}, {"black",0}};

    int max = -INFINITY;

    for (int i = 0; i < N; i++) {
        std::string str;
        std::cin >> str;
        markers[str]++;
    }

    for (std::pair<std::string, int> p : markers) {
        max = std::max(max, p.second);
    }

    printf("%d", std::min(max, N-max+1) + N-max);
}