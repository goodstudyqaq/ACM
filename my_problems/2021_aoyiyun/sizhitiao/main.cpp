// 撕纸条标程
#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n;
	cin >> n;
	vector< int > a(n + 1, 0);
	int sum = 0;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		sum += a[i];
		a[i] += a[i - 1];
	}

	int res = 0;
	for (int i = 1; i < n; i++) {
		if (a[i] == sum - a[i]) {
			res++;
		}
	}
	cout << res << endl;
	return 0;
}