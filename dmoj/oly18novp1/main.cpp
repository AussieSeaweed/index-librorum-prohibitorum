#include <iostream>

int n;
std::pair<int, int> segments[1000000];

int main() {
    scanf("%d", &n);

    for (int i = 0; i < n; ++i)
        scanf("%d %d", &segments[i].first, &segments[i].second);

    std::sort(segments, segments + n);

    int end = 1000000, count = 0;

    for (int i = n - 1; i >= 0; --i)
        if (segments[i].second <= end)
            ++count, end = segments[i].first;

    printf("%d", count);

    return 0;
}