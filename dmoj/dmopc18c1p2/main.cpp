#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> numbers[100];
int N, K;

int main() {
    scanf("%d%d", &N, &K);

    for (int i = 0; i < N; i++) {
        int n;
        scanf("%d", &n);
        numbers[i % K].push_back(n);
    }

    for (int i = 0; i < K; i++)
        sort(numbers[i].begin(), numbers[i].end(), greater<int>());

    int prev = 0;

    for (int i = 0; i < N; i++) {
        if (numbers[i % K].back() > prev) {
            prev = numbers[i % K].back();
            numbers[i % K].pop_back();
        } else {
            printf("NO\n");
            return 0;
        }
    }

    printf("YES\n");

    return 0;
}