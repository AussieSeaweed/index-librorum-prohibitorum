#include <iostream>
#include <set>

int N;
std::set<int> elements;

int main() {
    std::cin >> N;

    while (N--) {
        int n;
        std::cin >> n;
        elements.insert(n);
    }

    std::cout << elements.size() << std::endl;

    return 0;
}