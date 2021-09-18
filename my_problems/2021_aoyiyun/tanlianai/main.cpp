#include <bits/stdc++.h>
using namespace std;
int main() {
	// freopen("data.in", "r", stdin);
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n;
	double p;
	cin >> n >> p;
	vector< double > a(n + 1);
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
	}
	vector< double > dp(n + 2, 0);
	for (int i = n; i >= 1; i--) {
		dp[i] = (1.0 - p * a[i]) * dp[i + 1] + 1;
	}
	cout << fixed << setprecision(6);
	cout << dp[1] << endl;
	return 0;
}