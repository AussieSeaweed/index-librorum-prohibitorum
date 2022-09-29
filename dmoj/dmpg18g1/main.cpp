#include <bits/stdc++.h>
#include <bits/extc++.h>
#define scan(x) do{while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0');}while(0)
char _;
#define INF 9000000000000000000
#define inf 2000000000
using namespace std;

int N, K, lowest_student = inf, has_student[1000001];
bool empty[1000001];

int main() {
    scan(N);
    scan(K);

    for (int i = 0; i < K; i++) {
        int index;
        scan(index);
        empty[index - 1] = true;
    }

    for (int i = 0; i <= K; i++) {
        int index;
        scan(index);
        has_student[index - 1] = i + 1;
        lowest_student = min(lowest_student, index - 1);
    }

    stack<int> st;

    for (int i = lowest_student, left = K; left; i = (i + 1) % N) {
        if (has_student[i]) {
            st.push(has_student[i]);
            has_student[i] = 0;
        }
        if (empty[i] && !st.empty()) {
            empty[i] = false;
            st.pop();
            left--;
        }
    }

    printf("%d\n", st.top());

    return 0;
}