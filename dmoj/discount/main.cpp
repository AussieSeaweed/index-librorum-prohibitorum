#include <iostream>

long long N, T;

int main() {
    long long c, d;
    
    std::cin >> N;
    std::cin >> T;
    
    long long count = 0;
    
    for (int i = 0; i < N; i++) {
        std::cin >> c;
        std::cin >> d;
        
        if ((c - (c * (d * 0.01))) <= T)
            count++;
    }
    
    std::cout << count << "\n";
    
    return 0;
}