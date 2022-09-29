#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> graph(100001);
vector<long long> nums(100001, 0);
vector<long long> sums(100001, 0);
vector<bool> visited(100001, false);
vector<int> indegree(100001, 0);
vector<int> outdegree(100001, 0);
vector<int> topo;
int N, M;

int main() {
    scanf("%d%d", &N, &M);
    while (M--) {
        int v, w;
        scanf("%d%d", &v, &w);
        graph[v].push_back(w);
        outdegree[v]++;
        indegree[w]++;
    }
    long long ans = 0;
    for (int i = N; i >= 1; i--) {
        if (!outdegree[i]) {
            nums[i] = 1;
            sums[i] = 0;
        } else {
            for (int adj : graph[i]) {
                sums[i] = (sums[i] + sums[adj] + nums[adj]) % 1000000007;
                nums[i] = (nums[i] + nums[adj]) % 1000000007;
            }
        }

        if (!indegree[i]) {
            ans = (ans + sums[i]) % 1000000007;
        }
    }
    printf("%lld", ans);
    return 0;
}