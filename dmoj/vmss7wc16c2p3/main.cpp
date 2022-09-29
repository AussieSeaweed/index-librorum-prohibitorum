#include <iostream>
using namespace std;

int a[1000001], arr[1000000], N, last[1000000], cur;

void get_input() {
    int A, B;
    fill(a, a + 1000001, -1);
    scanf("%d", &A);
    for (int i = 0; i < A; i++) {
        int n;
        scanf("%d", &n);
        a[n] = i;
    }
    scanf("%d", &B);
    N = 0;
    for (int i = 0; i < B; i++) {
        int n;
        scanf("%d", &n);
        if (a[n] != -1) {
            arr[N++] = a[n];
        }
    }
}

int main() {
    get_input();
    if (N) {
        last[0] = arr[0];
        cur = 0;
        for (int i = 0; i < N; i++) {
            int lo = 0, hi = cur, mid {};
            while (lo <= hi) {
                mid = lo + (hi - lo) / 2;
                if (arr[i] <= last[mid]) {
                    hi = mid - 1;
                } else {
                    lo = mid + 1;
                }
            }
            cur = max(cur, lo);
            last[lo] = arr[i];
        }
        printf("%d", cur + 1);
    } else {
        printf("0");
    }
    return 0;
}