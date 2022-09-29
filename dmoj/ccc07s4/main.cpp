#include <iostream>
#include <list>

std::list<int>* slides[10000];
int nums[10000];
int n;

int main() {
    scanf("%d", &n);

    for (int i = 1; i <= n; i++) {
        slides[i] = new std::list<int>;
        nums[i] = 0;
    }

    int x, y;

    while (1) {
        scanf("%d%d", &x, &y);
        if (x == 0 && y == 0)
            break;
        (*slides[y]).push_back(x);
    }

    for (int node : *slides[n])
        nums[node] = 1;

    for (int i = n - 1; i >= 1; i--)
        for (int node : *slides[i])
            nums[node] += nums[i];

    printf("%d", nums[1]);
    return 0;
}