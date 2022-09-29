#include <iostream>
#include <algorithm>

int arr[100000];
int n;

int main() {
    std::cin >> n;

    for (int i = 0; i < n; i++) {
        std::cin >> arr[i];
    }

    std::sort(arr, arr+n);

    for (int i = 0; i < n; i++) {
        std::cout << arr[i] << "\n";
    }

    return 0;
}