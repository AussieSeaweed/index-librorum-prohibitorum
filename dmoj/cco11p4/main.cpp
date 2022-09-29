#include <iostream>
#include <map>

using namespace std;

map<int, int> remaining;
int N;

int main() {
    scanf("%d", &N);

    remaining[0] = 1;

    while (N--) {
        int rnk;
        scanf("%d", &rnk);

        auto it = remaining.upper_bound(rnk);

        if (it == remaining.begin()) {
            printf("NO");
            return 0;
        }

        (--it)->second--;

        if (!it->second) {
            remaining.erase(it);
        }

        remaining[rnk] = 2;
    }

    printf("YES");

    return 0;
}