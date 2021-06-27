#include <bits/stdc++.h>
using namespace std;
int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		int n;
		scanf("%d", &n);
		int res = 0;
		int a;
		for (int i = 1; i <= n; i++) {
			scanf("%d", &a);
			res += a;
		}
		if (res == n) {
			puts("0");
			continue;
		} else if (res < n) {
			puts("1");
			continue;
		} else {
			cout << res - n << endl;
		}
	}
	return 0;
}