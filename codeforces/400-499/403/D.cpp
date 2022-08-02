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
// 最多 45 组
vector< vector< int > > f;

void init() {
	f.resize(1001, vector< int >(46, 0));
	// f[i][j] 区间长度和为 i，个数为 j 的方案数。
	// f[i][j] -> f[i + j][j], f[i + j + 1][j + 1]

	f[0][0] = 1;
	for (int i = 0; i < 1000; i++) {
		for (int j = 0; j <= 45; j++) {
			if (f[i][j] == 0) continue;
			if (i + j <= 1000 && j > 0)
				f[i + j][j] = (f[i + j][j] + f[i][j]) % mod;
			if (i + j + 1 <= 1000 && j + 1 <= 45)
				f[i + j + 1][j + 1] = (f[i + j + 1][j + 1] + f[i][j]) % mod;
		}
	}
}

int quick(int a, int b) {
	int res = 1;
	while (b) {
		if (b % 2) res = 1LL * res * a % mod;
		a = 1LL * a * a % mod;
		b /= 2;
	}
	return res;
}

vector< int > A, B;

void init2() {
	A.resize(1001);
	B.resize(1001);
	A[0] = 1;
	for (int i = 1; i <= 1000; i++) {
		A[i] = 1LL * A[i - 1] * i % mod;
	}
	B[1000] = quick(A[1000], mod - 2);
	for (int i = 999; i >= 0; i--) {
		B[i] = 1LL * B[i + 1] * (i + 1) % mod;
	}
}

int C(int n, int m) {
	return 1LL * A[n] * B[m] % mod * B[n - m] % mod;
}
vector< vector< int > > ans;

int main() {
#ifdef LOCAL
	freopen("data.in", "r", stdin);
#endif
	ios::sync_with_stdio(false);
	cin.tie(0);
	init();
	init2();
	ans.resize(1001, vector< int >(46, -1));

	int T;
	cin >> T;
	while (T--) {
		int n, k;
		cin >> n >> k;
		if (k > 45) {
			cout << 0 << '\n';
			continue;
		}
		if (ans[n][k] != -1) {
			cout << ans[n][k] << '\n';
			continue;
		}

		int res = 0;
		for (int len = (1 + k) * k / 2; len <= n; len++) {
			res = (res + f[len][k] * 1LL * C(n - len + k, k) % mod * A[k] % mod) % mod;
		}
		ans[n][k] = res;
		cout << res << '\n';
	}
	return 0;
}