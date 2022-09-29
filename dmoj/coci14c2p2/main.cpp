#include <iostream>
#include <unordered_set>

int main() {
    std::unordered_multiset<std::string> ppl;

    int N;
    scanf("%d", &N);

    for (int i = 0; i < N; i++) {
        std::string str;
        std::cin >> str;
        ppl.insert(str);
    }

    for (int i = 1; i < N; i++) {
        std::string str;
        std::cin >> str;

        ppl.erase(ppl.find(str));
    }

    std::cout << *ppl.begin();
}