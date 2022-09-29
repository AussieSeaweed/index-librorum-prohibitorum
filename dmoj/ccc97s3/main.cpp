#include <bits/stdc++.h>
#include <bits/extc++.h>
#define scan(x) do{while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0');}while(0)
char _;
#define INF 9000000000000000000
#define inf 2000000000
using namespace std;

int N;
char message[] { "Round %d: %d undefeated, %d one-loss, %d eliminated\n" };

void solve(int t) {
    int undefeated = t, one_loss = 0, eliminated = 0;
    int num_rounds = 0;

    printf(message, 0, undefeated, one_loss, eliminated);

    while (!(!undefeated && one_loss == 1)) {
        if (undefeated == 1 && one_loss == 1) {
            undefeated = 0;
            one_loss = 2;
        } else {
            int num_lost = one_loss / 2;
            eliminated += num_lost;
            one_loss -= num_lost;

            num_lost = undefeated / 2;
            one_loss += num_lost;
            undefeated -= num_lost;
        }

        printf(message, ++num_rounds, undefeated, one_loss, eliminated);
    }

    printf("There are %d rounds.\n", num_rounds);
}

int main() {
    scan(N);

    while (N--) {
        int t;
        scan(t);

        solve(t);
    }

    return 0;
}