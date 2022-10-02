#include <iostream>

int N, indices[300001];

int main() {
	std::cin >> N;

	for (int i = 0; i < N; ++i) {
		int book;
		std::cin >> book;
		indices[book] = i;
	}

	int count = 0, book = N - 1;

	while (book && indices[book] < indices[book + 1])
		++count, --book;

	std::cout << N - 1 - count << std::endl;

	return 0;
}
