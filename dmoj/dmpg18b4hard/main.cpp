#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

int main() {
    int N, M, X;
    scanf("%d%d%d", &N, &M, &X);

    std::vector<int> nums(N);
    std::vector<int> dens(M);

    for (int i = 0; i < N; i++)
        scanf("%d", &nums[i]);

    for (int i = 0; i < M; i++)
        scanf("%d", &dens[i]);

    std::sort(dens.begin(), dens.end());

    double closest = 9999999999999;
    int ans = -1;

    for (int d : dens) {
        bool flag = false;
        double sum = 0;
        for (int n : nums) {
            sum += n;
            if (n > d) {
                flag = true;
                break;
            }
        }
        sum /= d;
        sum /= N;

        if (sum < 0.5 || flag)
            continue;

        double offset = std::abs(sum * 100 - X);
        if (offset <= closest + 1E-6) {
            closest = offset;
            ans = d;
        }
    }

    if (ans == -1)
        printf("Shimnanigans have failed\n");
    else
        printf("%d\n", ans);
}