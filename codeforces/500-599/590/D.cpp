#include <bits/stdc++.h>

using namespace std;

template < typename A, typename B >
string to_string(pair< A, B > p);

template < typename A, typename B, typename C >
string to_string(tuple< A, B, C > p);

template < typename A, typename B, typename C, typename D >
string to_string(tuple< A, B, C, D > p);

string to_string(const string& s) {
	return '"' + s + '"';
}

string to_string(const char* s) {
	return to_string(( string )s);
}

string to_string(bool b) {
	return (b ? "true" : "false");
}

string to_string(vector< bool > v) {
	bool first = true;
	string res = "{";
	for (int i = 0; i < static_cast< int >(v.size()); i++) {
		if (!first) {
			res += ", ";
		}
		first = false;
		res += to_string(v[i]);
	}
	res += "}";
	return res;
}

template < size_t N >
string to_string(bitset< N > v) {
	string res = "";
	for (size_t i = 0; i < N; i++) {
		res += static_cast< char >('0' + v[i]);
	}
	return res;
}

template < typename A >
string to_string(A v) {
	bool first = true;
	string res = "{";
	for (const auto& x : v) {
		if (!first) {
			res += ", ";
		}
		first = false;
		res += to_string(x);
	}
	res += "}";
	return res;
}

template < typename A, typename B >
string to_string(pair< A, B > p) {
	return "(" + to_string(p.first) + ", " + to_string(p.second) + ")";
}

template < typename A, typename B, typename C >
string to_string(tuple< A, B, C > p) {
	return "(" + to_string(get< 0 >(p)) + ", " + to_string(get< 1 >(p)) + ", " + to_string(get< 2 >(p)) + ")";
}

template < typename A, typename B, typename C, typename D >
string to_string(tuple< A, B, C, D > p) {
	return "(" + to_string(get< 0 >(p)) + ", " + to_string(get< 1 >(p)) + ", " + to_string(get< 2 >(p)) + ", " + to_string(get< 3 >(p)) + ")";
}

void debug_out() {
	cerr << endl;
}

template < typename Head, typename... Tail >
void debug_out(Head H, Tail... T) {
	cerr << " " << to_string(H);
	debug_out(T...);
}

#ifdef LOCAL
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
#else
#define debug(...) 42
#endif

int main() {
#ifdef LOCAL
	freopen("data.in", "r", stdin);
#endif
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n, k, s;
	cin >> n >> k >> s;
	vector< int > q(n + 1);
	for (int i = 1; i <= n; i++) {
		cin >> q[i];
	}

	if (s > n * n) {
		sort(q.begin() + 1, q.begin() + 1 + n);
		int sum = 0;
		for (int i = 1; i <= k; i++) sum += q[i];
		cout << sum << endl;
		return 0;
	}

	const int inf = 0x3f3f3f3f;
	vector< vector< vector< int > > > dp(2, vector< vector< int > >(k + 1, vector< int >(n * n + 1, inf)));
	dp[0][0][0] = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j <= min(k, i); j++) {
			for (int p = 0; p <= n * n; p++) {
				int idx = i % 2;
				dp[idx][j][p] = inf;
				if (p != 0) {
					dp[idx][j][p] = min(dp[idx][j][p], dp[idx][j][p - 1]);
				}
				dp[idx][j][p] = min(dp[idx][j][p], dp[idx ^ 1][j][p]);

				if (j - 1 >= 0 && p >= (i - j))
					dp[idx][j][p] = min(dp[idx][j][p], dp[idx ^ 1][j - 1][p - (i - j)] + q[i]);
				debug(i, j, p, dp[idx][j][p]);
			}
		}
	}

	int M = k * (k + 1) / 2 + s;
	cout << dp[n % 2][k][s] << endl;
	return 0;
}