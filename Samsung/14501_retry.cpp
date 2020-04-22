#include <iostream>
#include <vector>
#include <algorithm>

int retirement (int N, std::vector<int> &T, std::vector<int> &P) {
	std::vector<int> profit(N+1);

	for (int i=0; i<=N; i++) {
		if (i > 0)
			profit.at(i) = std::max(profit.at(i), profit.at(i-1));
		if (i+T.at(i) <= N)
			profit.at(i+T.at(i)) = std::max(profit.at(i+T.at(i)), profit.at(i)+P.at(i));
	}

	return profit.at(N);
}

int main (void) {
	std::vector<int> T;
	std::vector<int> P;
	int N, t, p;

	std::cin >> N;

	for (int i=0; i<N; i++) {
		std::cin >> t >> p;
		T.push_back(t);
		P.push_back(p);
	}
	T.push_back(0);
	P.push_back(0);

	std::cout << retirement(N, T, P);

	return 0;
}
