#include <iostream>
#include <vector>
using namespace std;

int A[3], B[3], C[3];
vector<int> subset;

int main() {
    scanf("%d%d%d%d%d%d%d%d%d", A, A + 1, A + 2, B, B + 1, B + 2, C, C + 1, C + 2);

    if (A[2] == B[0]) subset.push_back(C[0]);
    if (A[0] == B[1]) subset.push_back(C[1]);
    if (A[1] == B[2]) subset.push_back(C[2]);

    int ans = 0;

    for (int i = 0; i < subset.size(); i++) {
        ans = max(ans, subset[i]);
        for (int j = i + 1; j < subset.size(); j++) {
            ans = max(ans, subset[i] + subset[j]);
            for (int k = j + 1; k < subset.size(); k++) {
                ans = max(ans, subset[i] + subset[j] + subset[k]);
            }
        }
    }

    printf("%d", ans);
    return 0;
}