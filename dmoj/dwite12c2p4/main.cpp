#include <bits/stdc++.h>
#include <bits/extc++.h>
#define pscan(x) do{while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0');}while(0)
#define scan(x) do{while((x=getchar())<'-'); _ssign=x=='-'; if(_ssign) while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0'); x=_ssign?-x:x;}while(0)
char _; bool _ssign;
template<typename T> inline constexpr const T&_min(const T&x,const T&y) {return x<y?x:y;}
template<typename T> inline constexpr const T&_max(const T&x,const T&y) {return x<y?y:x;}
template<typename T,typename...Ts> inline constexpr const T&_min(const T&x,const Ts&...xs) {return _min(x,_min(xs...));}
template<typename T,typename...Ts> inline constexpr const T&_max(const T&x,const Ts&...xs) {return _max(x,_max(xs...));}
#define min(...) _min(__VA_ARGS__)
#define max(...) _max(__VA_ARGS__)
#define INF 9000000000000000000
#define inf 2000000000
using namespace std;
using namespace __gnu_pbds;
template<typename T, typename Compare = std::less<T>>
using rbtset = tree<T, null_type, Compare, rb_tree_tag, tree_order_statistics_node_update>;
template<typename Key, typename Value, typename Compare = std::less<Key>>
using rbtmap = tree<Key, Value, Compare, rb_tree_tag, tree_order_statistics_node_update>;


int N;
rbtset<int> cards;

int main() {
    int t = 5;
    while (t--) {
        scan(N);
        cards.clear();
        for (int i = 1; i <= N; i++) {
            cards.insert(i);
        }

        vector<int> ans;
        bool valid = true;

        for (int i = 1; i <= N && valid; i++) {
            int index;
            scan(index);
            index = cards.size() - 1 - index;

            if (index < 0) {
                valid = false;
                break;
            }

            auto it = cards.find_by_order(index);
            ans.push_back(*it);
            cards.erase(it);
        }

        if (valid) {
            for (int i : ans)
                printf("%d ", i);
            printf("\n");
        } else {
            printf("IMPOSSIBLE\n");
        }
    }
    return 0;
}