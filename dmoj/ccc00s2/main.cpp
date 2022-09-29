#include <bits/stdc++.h>

int main() {
    int N;
    scanf("%d", &N);
    std::vector<double> streams(N+1);

    for (int i = 1; i <= N; i++) {
        scanf("%lf", &streams[i]);
    }

    while (1) {
        int t;
        scanf("%d", &t);

        if (t == 77)
            break;
        else if (t == 99) {
            int a, b;
            scanf("%d%d", &a, &b);
            streams.insert(streams.begin()+a, streams[a]);
            streams[a] *= ((double) b)/100;
            streams[a+1] -= streams[a];
        } else if (t == 88) {
            int a;
            scanf("%d", &a);
            streams[a] += streams[a+1];
            streams.erase(streams.begin()+(a+1));
        }
    }

    for (int i = 1 ; i < streams.size(); i++)
        printf("%d ", (int) round(streams[i]));
}