#include <bits/stdc++.h>

int main() {
    int t, s, h;
    scanf("%d%d%d", &t, &s, &h);

    while (t--) {
        printf("*");
        for (int i = 0; i < s; i++)
            printf(" ");
        printf("*");
        for (int i = 0; i < s; i++)
            printf(" ");
        printf("*\n");
    }

    printf("*");
    for (int i = 0; i < s; i++)
        printf("*");
    printf("*");
    for (int i = 0; i < s; i++)
        printf("*");
    printf("*\n");

    while (h--) {
        printf(" ");
        for (int i = 0; i < s; i++)
            printf(" ");
        printf("*\n");
    }
}