#include <iostream>
#include <vector>
#include <algorithm>

int N, S, L, P[1000], M[1000], G[1000];
std::vector<int> left, right;

bool pOrder(int a, int b) {
	return P[a] < P[b];
}

int main() {
	std::cin >> N >> S >> L;

	for (int i = 0; i < N; ++i) {
		std::cin >> P[i] >> M[i] >> G[i];

		if (P[i] < S)
			left.push_back(i);
		else
			right.push_back(i);
	}

	std::sort(left.begin(), left.end(), pOrder);
	std::sort(right.begin(), right.end(), pOrder);
	std::reverse(right.begin(), right.end());

	bool flag = true;

	while (flag) {
		flag = false;

		if (!left.empty() && L >= M[left.back()]) {
			L += G[left.back()];
			left.pop_back();
			flag = true;
		}

		if (!right.empty() && L >= M[right.back()]) {
			L += G[right.back()];
			right.pop_back();
			flag = true;
		}
	}

	std::cout << L << std::endl;

	return 0;
}
