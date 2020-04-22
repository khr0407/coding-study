class Solution {
public:
	int reverse (int x) {
		int reverse = 0;
		bool isPositive = true;

		if (x < 0) {
			if (x == INT_MIN-1) return 0;	// overflow
			isPositive = false;
			x *= -1;
		}

		while (x != 0) {
      if (reverse > INT_MAX/10) return 0;	// overflow
			reverse = reverse*10 + x%10;
			x /= 10;
		}

		if (isPositive) return reverse;
		else return (-1)*reverse;
	}
};
