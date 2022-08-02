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

	int n, m, s, e;
	cin >> n >> m >> s >> e;
	vector< int > a(n + 1);
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
	}
	vector< vector< int > > b_idx(1e5 + 1);
	for (int i = 1; i <= m; i++) {
		int b;
		cin >> b;
		b_idx[b].push_back(i);
	}
	int LIMIT = s / e;
	vector< vector< int > > dp(n + 1, vector< int >(LIMIT + 1, m + 1));
	int ans = 0;
	for (int i = 0; i <= n; i++) {
		dp[i][0] = 0;
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= min(i, LIMIT); j++) {
			dp[i][j] = dp[i - 1][j];
			int val = a[i];
			// dp[i - 1][j - 1]
			if (b_idx[val].size()) {
				int the_val = dp[i - 1][j - 1];
				int idx = upper_bound(b_idx[val].begin(), b_idx[val].end(), the_val) - b_idx[val].begin();
				if (idx != b_idx[val].size()) {
					int real_idx = b_idx[val][idx];
					dp[i][j] = min(dp[i][j], real_idx);
				}
			}
			debug(i, j, dp[i][j], j * e + i + dp[i][j], s);

			if (dp[i][j] != m + 1 && j * e + i + dp[i][j] <= s) {
				ans = max(ans, j);
			}
		}
	}
	cout << ans << endl;
	return 0;
}