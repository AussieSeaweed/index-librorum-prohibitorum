#include <iostream>
#include <vector>
#include <queue>

std::string bfs(int n) {
    std::queue<std::pair<std::string, int>> q;
    q.emplace("1", 1);
    
    while (!q.empty()) {
        auto p = q.front(); q.pop();
        
        std::string str = p.first;
        int num = p.second;
        
        if (num % n == 0)
            return str;
            
        num %= n;
        
        q.emplace(str + "0", num * 10);
        q.emplace(str + "1", num * 10 + 1);
    }
}

int main() {
    int _;
    scanf("%d", &_);
    
    while (_--) {
        int n;
        scanf("%d", &n);
        
        std::cout << bfs(n) << "\n";
    }
}