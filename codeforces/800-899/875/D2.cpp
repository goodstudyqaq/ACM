#include <bits/stdc++.h>

using namespace std;

typedef long long LL;

const int maxn = 200005;
int n, a[maxn];
bool check(int l, int r) {
	set< int > S;
	int val = 0;
	for (int i = l; i <= r; i++) {
		val |= a[i];
		S.insert(a[i]);
	}
	if (S.count(val)) return false;
	return true;
}
int main() {
	freopen("data.in", "r", stdin);
	int n;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
	}

	int res = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = i + 1; j <= n; j++) {
			if (check(i, j)) {
				cout << i << ' ' << j << endl;
				res++;
			}
		}
	}
	cout << res << endl;
}