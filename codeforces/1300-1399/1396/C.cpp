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
	int n, r1, r2, r3, d;
	cin >> n >> r1 >> r2 >> r3 >> d;
	vector< int > a(n + 1);
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
	}

	vector< vector< long long > > dp(n + 1, vector< long long >(2, 0));
	dp[1][0] = 1LL * a[1] * r1 + r3;
	dp[1][1] = min(1LL * a[1] * r1 + r1, 1LL * r2);

	for (int i = 2; i <= n; i++) {
		dp[i][0] = min({ dp[i - 1][0] + d + 1LL * a[i] * r1 + r3, dp[i - 1][1] + d + 1LL * a[i] * r1 + r3 + d + r1 + d, dp[i - 1][1] + d + 1LL * a[i] * r1 + r1 + d + r1 + d + r1, dp[i - 1][1] + d + r2 + d + r1 + d + r1 });
		dp[i][1] = min({ dp[i - 1][0] + d + 1LL * a[i] * r1 + r1, dp[i - 1][0] + d + r2, dp[i - 1][1] + d + 1LL * a[i] * r1 + r1 + d + r1 + d, dp[i - 1][1] + d + r2 + d + r1 + d });
	}

	long long ans = min(dp[n][0], dp[n - 1][1] + d + 1LL * a[n] * r1 + r3 + d + r1);
	cout << ans << endl;
	return 0;
}