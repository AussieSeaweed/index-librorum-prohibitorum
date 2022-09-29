#include <bits/stdc++.h>
using namespace std;
int main() {
	int T = 10;
	while (T--) {
		int N;
		cin >> N; 
		int ind;
		map<int, vector<int> > index;
		map<int, int> lowest;
		vector<int> indices;
		int low = 9999999;
		for (int i = 0; i < N; i++) {
			cin >> ind;
			indices.push_back(ind);
			int r;
			cin >> r;
			vector<int> cur(r);
			for (int j = 0; j < r; j++) {
				cin >> cur[j];
				low = min(low, cur[j]);
			}
			index[ind] = cur;
		}
		vector<int> sL;
		for (int ind : indices) {
			for (int j : index[ind]) {
				if (j == low) {
					sL.push_back(ind);
					break;
				}
			}
		}
		sort(sL.begin(), sL.end());
		cout << low << " {";
		for (int i = 0; i < sL.size() - 1; i++) {
			cout << sL[i] << ",";
		}
		cout << sL.back();
		cout << "}" << endl;
	}
}