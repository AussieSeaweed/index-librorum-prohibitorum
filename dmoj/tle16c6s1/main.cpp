#include <iostream>
#include <unordered_map>
#include <algorithm>

std::unordered_map<std::string, int> pref;
std::pair<int, int> things[100000];
int T, N;

int main() {
    scanf("%d", &T);

    for (int i = 0; i < T; i++) {
        std::string str;
        std::cin >> str;
        pref[str] = i;
    }

    scanf("%d", &N);

    for (int i = 0; i < N; i++) {
        std::string str;
        std::cin >> str;
        things[i].first = pref[str];
        things[i].second = i + 1;
    }

    std::sort(things, things + N);

    for (int i = 0; i < N; i++) {
        printf("%d\n", things[i].second);
    }

    return 0;
}