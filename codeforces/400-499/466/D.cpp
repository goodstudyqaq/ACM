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

const int mod = 1e9 + 7;
int main() {
#ifdef LOCAL
	freopen("data.in", "r", stdin);
#endif
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n, h;
	cin >> n >> h;
	vector< int > a(n + 1);
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
	}

	vector< vector< int > > dp(n + 1, vector< int >(n + 1, 0));

	if (a[1] == h) {
		dp[1][0] = 1;
	} else if (a[1] == h - 1) {
		dp[1][1] = 1;
		dp[1][0] = 1;
	} else {
		cout << 0 << endl;
		return 0;
	}

	for (int i = 2; i <= n; i++) {
		int val = a[i];
		if (val > h) {
			cout << 0 << endl;
			return 0;
		}
		int tmp = h - val;

		(dp[i][tmp] += dp[i - 1][tmp]) %= mod;
		if (tmp > 0)
			(dp[i][tmp] += dp[i - 1][tmp - 1]) %= mod;
		debug(i, tmp, dp[i][tmp]);

		if (tmp > 0) {
			tmp--;
			dp[i][tmp] = (dp[i][tmp] + 1LL * (tmp + 1) * dp[i - 1][tmp + 1] % mod) % mod;
			dp[i][tmp] = (dp[i][tmp] + 1LL * (tmp + 1) * dp[i - 1][tmp] % mod) % mod;
			debug(i, tmp, dp[i][tmp]);
		}
	}
	cout << dp[n][0] << endl;
}