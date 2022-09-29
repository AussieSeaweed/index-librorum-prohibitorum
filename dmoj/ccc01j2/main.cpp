#include <iostream>

int main() {
    int x, m;
    scanf("%d%d", &x, &m);
    for (int n = 0; n < m; n++) {
        if (x * n % m == 1) {
            printf("%d", n);
            return 0;
        }
    }
    printf("No such integer exists.");
    return 0;
}