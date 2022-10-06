#include <iostream>

int T, N, A[1000000];

int sign(int a) {
	return a / std::abs(a);
}

int main() {
	std::cin >> T;

	while (T--) {
		std::cin >> N;
		
		for (int i = 0; i < N; ++i)
			std::cin >> A[i];

		int a = 0;
		bool flag = false;

		for (int i = 1; i < N && !flag; ++i) {
			if (A[i - 1] && A[i]) {
				int b = A[i - 1] == A[i] ? 0 : (sign(A[i - 1] - A[i]) * ((i & 1) ? 1 : -1));

				if (!a)
					a = b;

				if (!b || a != b)
					flag = true;
			}
		}

		std::cout << (flag ? "NO" : "YES") << std::endl;
	}

	return 0;
}
