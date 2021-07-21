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

int cal(int val) {
	vector< int > v(5);
	int now_idx = 0;
	while (val) {
		v[now_idx++] = val % 2;
		val /= 2;
	}

	int now = 0;
	int mx = 0;
	while (now < v.size()) {
		int go = now;
		while (go < v.size() && v[go] == v[now]) {
			go++;
		}
		mx = max(mx, go - now);
		now = go;
	}
	return mx;
}

const int mod = 998244353;

long long dp[501][501];

long long T(int n, int k) {
	if (k < 1 || k > n) return 0;
	if (k == 1 || k == n) return 2;
	if (dp[n][k] != -1) return dp[n][k];
	return dp[n][k] = ((((((2LL * T(n - 1, k) % mod + T(n - 1, k - 1)) % mod - 2LL * T(n - 2, k - 1) % mod) % mod + mod) % mod + T(n - k, k - 1)) % mod - T(n - k - 1, k)) % mod + mod) % mod;
}

long long inv2 = 499122177;
int main() {
#ifdef LOCAL
	freopen("data.in", "r", stdin);
#endif
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n, k;
	cin >> n >> k;
	memset(dp, -1, sizeof(dp));
	long long res = 0;

	for (int i = 1; i <= n; i++) {
		debug(i, T(n, i));
	}

	for (int i = 1; i <= n; i++) {
		if (i >= k) break;
		long long res1 = T(n, i);
		int other = min(k / i, n);
		if (other * i == k) other--;
		for (int j = 1; j <= other; j++) {
			long long res2 = T(n, j);
			res = (res + res1 * res2 % mod * inv2 % mod) % mod;
		}
	}
	cout << res << endl;
}