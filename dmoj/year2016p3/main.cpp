#include <bits/stdc++.h>

int main() {
    int N;
    scanf("%d", &N);

    std::vector<int> nums;

    for (int i = 0; i < N; i++) {
        int n;
        scanf("%d", &n);
        nums.push_back(n);
    }

    std::sort(nums.begin(), nums.end());

    int max_size = -INFINITY;
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            int desired = nums[j] - nums[i] + nums[j];
            for (int k = j + 1; k < N && nums[k] <= desired; k++) {
                if (nums[k] == desired)
                    max_size = std::max(max_size, nums[i] + nums[j] + nums[k]);
            }
        }
    }

    printf("%d", max_size);
}