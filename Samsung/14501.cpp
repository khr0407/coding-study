#include <stdio.h>
#include <stdlib.h>

struct Schedule {
	int t;
	int p;
};

int N;
int max_sum;
struct Schedule sd[15];

void counsel (int n, int sum) {
	int next_n = n + sd[n].t;
	int next_sum = sum + sd[n].p;

	if (next_n >= N) {
		if (next_n == N && next_sum > max_sum) max_sum = next_sum; // end
		if (next_n > N && sum > max_sum) max_sum = sum; // end
		for (int i=n+1; i<N; i++) return counsel(i, sum);	// skip
		return;
	}

	// no skipping
	if (sd[n].t == 1) return counsel(next_n, next_sum);

	counsel(next_n, next_sum);
	// skip
	for (int i=1; i<N-n; i++) {
		if (n+i < N && n+i+sd[n+i].t <= N) counsel(n+i, sum);
	}
}

int main (void) {
	scanf("%d", &N);

	for (int i=0; i<N; i++) {
		scanf("%d %d", &sd[i].t, &sd[i].p);
	}

	for (int i=0; i<N; i++) counsel(i, 0);

	printf("%d\n", max_sum);

	return 0;
}
