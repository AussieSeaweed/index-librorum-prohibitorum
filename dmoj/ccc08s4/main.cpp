#include <bits/stdc++.h>

int ans;
std::vector<int> cards(4);
std::vector<bool> used(4);

void find(int s, std::stack<int> st) {
    if (s == 4 && st.size() == 1) {
        if (st.top() > ans && st.top() <= 24)
            ans = st.top();
        return;
    }

    if (s < 4) {
        for (int i = 0; i < 4; i++) {
            if (!used[i]) {
                used[i] = true;
                std::stack<int> newst = st;
                newst.push(cards[i]);
                find(s+1, newst);
                used[i] = false;
            }
        }
    }

    if (st.size() >= 2) {
        auto temp = st;
        int a = temp.top(); temp.pop();
        int b = temp.top(); temp.pop();

        auto t1 = temp;
        t1.push(a+b);
        find(s,t1);

        auto t2 = temp;
        t2.push(a-b);
        find(s,t2);

        auto t3 = temp;
        t3.push(a*b);
        find(s,t3);

        if (b != 0 && a % b == 0) {
            auto t4 = temp;
            t4.push(a/b);
            find(s, t4);
        }
    }
}

int main() {
    int N;
    scanf("%d", &N);

    while (N--) {
        ans = -INFINITY;

        for (int i = 0; i < 4; i++) {
            scanf("%d", &cards[i]);
            used[i] = false;
        }

        find(0, std::stack<int>());
        printf("%d\n", ans);
    }
}