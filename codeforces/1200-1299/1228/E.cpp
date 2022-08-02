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

int quick(int a, int b) {
	int res = 1;
	while (b) {
		if (b % 2) res = 1LL * res * a % mod;
		b /= 2;
		a = 1LL * a * a % mod;
	}
	return res;
}

const int maxn = 251;
int A[maxn], B[maxn];

void init() {
	A[0] = 1;
	for (int i = 1; i < maxn; i++) {
		A[i] = 1LL * A[i - 1] * i % mod;
	}
	B[maxn - 1] = quick(A[maxn - 1], mod - 2);
	for (int i = maxn - 2; i >= 0; i--) {
		B[i] = 1LL * B[i + 1] * (i + 1) % mod;
	}
}

int C(int n, int m) {
	return 1LL * A[n] * B[m] % mod * B[n - m] % mod;
}

int main() {
#ifdef LOCAL
	freopen("data.in", "r", stdin);
#endif
	ios::sync_with_stdio(false);
	cin.tie(0);
	init();

	int n, k;
	cin >> n >> k;
	vector< vector< int > > dp;
	dp.resize(n + 1, vector< int >(n + 1, 0));
	dp[0][0] = 1;
	vector< int > k_pow(n + 1), k_1_pow(n + 1);
	k_pow[0] = 1, k_1_pow[0] = 1;
	for (int i = 1; i <= n; i++) {
		k_pow[i] = 1LL * k_pow[i - 1] * k % mod;
		k_1_pow[i] = 1LL * k_1_pow[i - 1] * (k - 1) % mod;
	}

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			// 特判 0
			for (int a = 0; a <= j; a++) {
				if (j == a) {
					dp[i][j] = (dp[i][j] + 1LL * dp[i - 1][a] * (k_pow[j] - k_1_pow[j]) % mod * k_1_pow[n - j] % mod) % mod;
				} else {
					dp[i][j] = (dp[i][j] + 1LL * dp[i - 1][a] * k_pow[a] % mod * C(n - a, j - a) % mod * k_1_pow[n - j] % mod) % mod;
				}
			}
			// debug(i, j, dp[i][j]);
		}
	}
	dp[n][n] = (dp[n][n] + mod) % mod;
	cout << dp[n][n] << endl;
	return 0;
}