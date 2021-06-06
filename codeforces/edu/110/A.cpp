#include <bits/stdc++.h>
using namespace std;
int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		int a[5];
		int b[5];
		for (int i = 1; i <= 4; i++) {
			scanf("%d", &a[i]);
			b[i] = a[i];
		}
		sort(a + 1, a + 1 + 4);
		if ((a[4] == b[1] || a[4] == b[2]) && (a[3] == b[3] || a[3] == b[4])) {
			puts("YES");
			continue;
		}
		if ((a[4] == b[3] || a[4] == b[4]) && (a[3] == b[1] || a[3] == b[2])) {
			puts("YES");
			continue;
		}
		puts("NO");
	}
}