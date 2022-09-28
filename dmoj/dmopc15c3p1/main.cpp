#include <iostream>

int a, b, c, d;

int main() {
    std::cin >> a >> b >> c >> d;
    std::cout << (std::min(b, d) - std::max(a, c) > 0 ? "YES" : "NO") << std::endl;

    return 0;
}
