#include <iostream>
#include <queue>

int R, C, K, D[50000][10];

int solve(int c) {
	int count = 0;
	std::queue<int> q;

	for (int r = 0; r < R; ++r) {
		if (!q.empty() && q.front() < r - K)
			q.pop();

		if (D[r][c] == 1)
			q.push(r);
		else if (D[r][c] == 2)
			count += !q.empty();
	}

	return count;
}

int main() {
	std::cin >> R >> C >> K;

	for (int r = 0; r < R; ++r)
		for (int c = 0; c < C; ++c)
			std::cin >> D[r][c];

	int count = 0;

	for (int c = 0; c < C; ++c)
		count += solve(c);

	std::cout << count << std::endl;

	return 0;
}
