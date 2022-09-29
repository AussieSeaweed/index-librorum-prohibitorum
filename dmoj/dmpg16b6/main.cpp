#include <bits/stdc++.h>


int main() {
    int N;
    std::cin >> N;

    while (N--) {
        char t;
        std::cin >> t;

        if (t == 'A') {
            std::string x;
            std::cin >> x;
            long long ans = 0;
            int count = 0;
            for (int i = x.size() - 1; i >= 0; i--, count++)
                if (x[i] == '1')
                    ans += round(pow(-2, count));
            printf("%lld\n", ans);
        } else {
            int x;
            std::cin >> x;
            std::string str;
            while (x != 0) {
                int rem = x % -2;
                x /= -2;

                if (rem < 0) {
                    x++;
                }

                if (rem) {
                    str = "1" + str;
                } else {
                    str = "0" + str;
                }
            }
            std::cout << (str.empty() ? "0" : str) << "\n";
        }
    }

    return 0;
}