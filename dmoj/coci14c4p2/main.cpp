#include <iostream>
#include <deque>
#include <unordered_map>
#include <algorithm>
#include <cassert>

int counts[100001];
std::deque<int> heights;
int N;

int main() {
	std::cin >> N;

	for (int i = 0; i < N; ++i) {
		int height;
		std::cin >> height;

		counts[height]++;
	}

	for (int i = 1; i <= 100000; ++i)
		if (counts[i])
			heights.push_back(i);

	std::string winner = "Slavko";

	while (heights.size() > 2) {
		if (counts[heights.front()] < counts[heights.back()])
			winner = "Mirko";
		else
			winner = "Slavko";

		int count = std::min(counts[heights.front()], counts[heights.back()]);

		counts[heights.front()] -= count;
		counts[heights[1]] += count;
		counts[heights[heights.size() - 2]] += count;
		counts[heights.back()] -= count;

		if (!counts[heights.front()])
			heights.pop_front();
		if (!counts[heights.back()])
			heights.pop_back();
	}

	std::cout << winner << std::endl;
	std::cout << heights.front() << ' ' << heights.back() << std::endl;

	return 0;
}
