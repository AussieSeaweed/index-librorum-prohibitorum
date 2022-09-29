#include <bits/stdc++.h>
int main() {
    int N, M;
    scanf("%d%d", &N, &M);

    int ans;

    if (N >= M)
        ans = M - 1;
    else
        ans = std::min(N, M - 1);

    printf("%d", ans);
}