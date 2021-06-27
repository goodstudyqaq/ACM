#include <bits/stdc++.h>
using namespace std;
int main() {
	srand(time(NULL));
	int n = rand() % 10 + 1;
	freopen("data.in", "w", stdout);
	printf("%d\n", n);
	for (int i = 1; i <= n; i++) {
		int val = rand() % 100;
		printf("%d ", val);
	}
	puts("");
}