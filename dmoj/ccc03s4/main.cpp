#include <iostream>
#include <algorithm>

std::string substr[5005];
int N;

int get_lcp(std::string a, std::string b) {
    int n = std::min(a.size(), b.size());
    for (int i = 0; i < n; i++)
        if (a[i] != b[i])
            return i;

    return n;
}

int main() {
    scanf("%d", &N);
    std::string str;

    for (int i = 0; i < N; i++) {
        std::cin >> str;

        for (int j = 0; j < str.size(); j++)
            substr[j] = str.substr(j, str.size()-j);

        std::sort(substr, substr + str.size());

        int count = substr[0].size() + 1;
        for (int j = 1; j < str.size(); j++) {
            count += substr[j].size() - get_lcp(substr[j], substr[j-1]);
        }

        printf("%d\n", count);
    }
    return 0;
}