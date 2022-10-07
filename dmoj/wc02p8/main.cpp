#include <iostream>
#include <vector>

void psa(std::vector<int> &A) {
	for (int i = 1; i < A.size(); ++i) A[i] += A[i - 1];
	A.insert(A.begin(), 0);
}

int subsum(const std::vector<int> &A, int begin, int end) {
	return A[end] - A[begin];
}

int test(std::vector<int> &A, int X) {
	int count = 0;

	for (int begin = 0, end = 0; end <= A.size(); ++end) {
		while (subsum(A, begin, end) > X)
			++begin;

		if (subsum(A, begin, end) == X)
			++count;
	}

	return count;
}

int main() {
	int N;
	std::cin >> N;

	std::vector<int> A(N);
	for (int i = 0; i < N; ++i)
		std::cin >> A[i];

	psa(A);

	int T;
	std::cin >> T;

	while (T--) {
		int t;
		std::cin >> t;

		std::cout << test(A, t) << ' ';
	}

	std::cout << std::endl;

	return 0;
}
