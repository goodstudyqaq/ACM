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
	int n, W, B, X;
	cin >> n >> W >> B >> X;
	vector< int > c(n + 1), cost(n + 1);
	int num = 0;
	for (int i = 1; i <= n; i++) {
		cin >> c[i];
		num += c[i];
	}
	for (int i = 1; i <= n; i++) {
		cin >> cost[i];
	}

	vector< vector< long long > > dp(n + 1, vector< long long >(num + 1, -2e13));
	num = 0;
	dp[0][0] = W;
	for (int i = 1; i <= n; i++) {
		num += c[i];
		for (int j = 0; j <= num; j++) {
			for (int k = 0; k <= j && k <= c[i]; k++) {
				int bef = j - k;
				if (bef > num - c[i]) continue;
				long long tmp = min(1LL * dp[i - 1][bef] + X, 1LL * W + 1LL * (j - k) * B);
				if (tmp - 1LL * cost[i] * k >= 0)
					dp[i][j] = max(dp[i][j], tmp - 1LL * cost[i] * k);
			}
			debug(i, j, dp[i][j]);
		}
	}

	int ans = 0;
	for (int i = 0; i <= num; i++) {
		if (dp[n][i] >= 0) ans = i;
	}
	cout << ans << endl;
	return 0;
}