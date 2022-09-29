#include <bits/stdc++.h>

int main() {
    int N;
    scanf("%d", &N);

    N--;

    int my;
    scanf("%d" ,&my);

    while (N--) {
        int your;
        scanf("%d", &your);
        
        if (your >= my) {
            printf("NO");
            return 0;
        }
    }

    printf("YES");
    return 0;
}