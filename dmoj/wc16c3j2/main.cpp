#include <iostream>
#include <vector>

bool zeroShot(const std::vector<int> &I) {
	for (int i = 1; i < I.size(); ++i)
		if (I[i - 1] >= I[i])
			return false;
	return true;
}

bool oneShot(const std::vector<int> &I) {
	std::vector<int> W;
	int D = I.size();

	for (auto it = I.crbegin(); it != I.crend();) {
		if (*it == D) {
			--D;
			++it;
		} else if (!W.empty() && W.back() == D) {
			--D;
			W.pop_back();
		} else
			W.push_back(*it++);
	}

	while (!W.empty() && W.back() == D) {
		--D;
		W.pop_back();
	}

	return W.empty();
}

int main() {
	int N;
	std::cin >> N;

	std::vector<int> S;

	for (int i = 0; i < N; ++i) {
		int s;
		std::cin >> s;
		S.push_back(s);
	}

	std::vector<int> I(S.rbegin(), S.rend());

	if (zeroShot(I))
		std::cout << 0 << std::endl;
	else if (oneShot(I))
		std::cout << 1 << std::endl;
	else
		std::cout << 2 << std::endl;

	return 0;
}
