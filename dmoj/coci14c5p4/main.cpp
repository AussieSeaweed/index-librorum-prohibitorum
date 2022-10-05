#include <iostream>

std::string up(std::string N) {
	std::string dp[2];

	for (int i = N.size() - 1; i >= 0; --i) {
		char c = N[i];
		int parity = c & 1;

		if (dp[!parity].empty()) {
			if (c < '9')
				dp[!parity] = std::string(1, c + 1);
			else
				dp[!parity].clear();

			if (c < '8')
				dp[parity] = std::string(1, c + 2);
			else
				dp[parity].clear();
		} else {
			dp[parity] = std::string(1, c) + dp[!parity];

			if (c < '9')
				dp[!parity] = std::string(1, c + 1);
			else
				dp[!parity].clear();
		}

		for (parity = 0; parity < 2; ++parity)
			if (!dp[parity].empty())
				while (dp[parity].size() < N.size() - i)
					dp[parity].push_back('0' + !(dp[parity].back() & 1));
	}

	if (dp[0].empty() && dp[1].empty()) {
		std::string s(1, '1');

		for (int i = 0; i < N.size(); ++i)
			s.push_back('0' + !(s.back() & 1));

		return s;
	} else if (dp[0].empty())
		return dp[1];
	else if (dp[1].empty())
		return dp[0];

	return std::min(dp[0], dp[1]);
}

std::string down(std::string N) {
	std::string dp[2];

	for (int i = N.size() - 1; i >= 0; --i) {
		char c = N[i];
		int parity = c & 1;

		if (dp[!parity].empty()) {
			if (c > '0')
				dp[!parity] = std::string(1, c - 1);
			else
				dp[!parity].clear();

			if (c > '1')
				dp[parity] = std::string(1, c - 2);
			else
				dp[parity].clear();
		} else {
			dp[parity] = std::string(1, c) + dp[!parity];

			if (c > '0')
				dp[!parity] = std::string(1, c - 1);
			else
				dp[!parity].clear();
		}

		for (parity = 0; parity < 2; ++parity)
			if (!dp[parity].empty())
				while (dp[parity].size() < N.size() - i)
					dp[parity].push_back('9' - (dp[parity].back() & 1));
	}

	if (dp[0].empty() && dp[1].empty()) {
		std::string s(1, '9');

		for (int i = 1; i < N.size(); ++i)
			s.push_back('9' - (s.back() & 1));

		return s;
	} else if (dp[0].empty())
		return dp[1];
	else if (dp[1].empty())
		return dp[0];

	return std::max(dp[0], dp[1]);
}

std::string diff(std::string lo, std::string hi) {
	bool carry = false;
	std::string result(lo.size(), '0');

	for (int i = result.size() - 1; i >= 0; --i) {
		if (lo[i] + carry > hi[i]) {
			result[i] = hi[i] + 10 - lo[i] - carry + '0';
			carry = true;
		} else {
			result[i] = hi[i] - lo[i] - carry + '0';
			carry = false;
		}
	}

	return result;
}

int compare(std::string lo, std::string N, std::string hi) {
	while(lo.size() < hi.size())
		lo.insert(lo.begin(), '0');

	while(N.size() < hi.size())
		N.insert(N.begin(), '0');

	std::string left = diff(lo, N);
	std::string right = diff(N, hi);

	if (left < right)
		return -1;
	else if (left > right)
		return 1;
	else
		return 0;
}

int main() {
	std::string N;
	std::cin >> N;

	std::string lo = down(N), hi = up(N);

	int o = compare(lo, N, hi);

	if (o == -1)
		std::cout << lo << std::endl;
	else if (o == 1)
		std::cout << hi << std::endl;
	else
		std::cout << lo << ' ' << hi << std::endl;

	return 0;
}
