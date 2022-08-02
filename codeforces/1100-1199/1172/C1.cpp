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

const int mod = 998244353;

int quick(int a, int b) {
	int res = 1;
	while (b) {
		if (b % 2) res = 1LL * res * a % mod;
		b /= 2;
		a = 1LL * a * a % mod;
	}
	return res;
}

vector< int > a, w;

int main() {
#ifdef LOCAL
	freopen("data.in", "r", stdin);
#endif
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n, m;
	cin >> n >> m;
	a.resize(n + 1);
	w.resize(n + 1);

	int cnt[2] = { 0 };
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		cnt[a[i]]++;
	}

	int sum[2] = { 0 };

	for (int i = 1; i <= n; i++) {
		cin >> w[i];
		sum[a[i]] += w[i];
	}

	vector< int > ans(n + 1, 0);
	for (int i = 1; i <= n; i++) {
		vector< vector< vector< int > > > dp;

		dp.resize(51, vector< vector< int > >(51, vector< int >(51, 0)));
		dp[0][0][0] = 1;

		for (int x = 0; x <= min(sum[0], m); x++) {
			for (int y = 0; y + x <= m; y++) {
				if (a[i] == 0) {
					for (int z = max(0, x - (sum[0] - w[i])); z <= min(x, w[i]); z++) {
						if (x == 0 && y == 0 && z == 0) continue;
						int res = 0;

						if (x > 0) {
							int down = sum[0] + sum[1] - (x - 1) + y;
							int up = sum[0] - (x - 1) - (w[i] - z);
							if (up >= 0 && down > 0)
								res = (res + 1LL * dp[x - 1][y][z] * up % mod * quick(down, mod - 2) % mod) % mod;
						}
						if (y > 0) {
							int down = sum[0] + sum[1] - x + y - 1;
							int up = sum[1] + y - 1;
							if (up >= 0 && down > 0)
								res = (res + 1LL * dp[x][y - 1][z] * up % mod * quick(down, mod - 2) % mod) % mod;
						}

						if (x > 0 && z > 0) {
							int down = sum[0] + sum[1] - (x - 1) + y;
							int up = w[i] - (z - 1);
							if (up >= 0 && down > 0)
								res = (res + 1LL * dp[x - 1][y][z - 1] * up % mod * quick(down, mod - 2) % mod) % mod;
						}
						dp[x][y][z] = res;

						if (x + y == m) {
							int val = w[i] - z;
							ans[i] = (ans[i] + 1LL * val * dp[x][y][z] % mod) % mod;
						}
					}
				} else {
					for (int z = 0; z <= y; z++) {
						if (x == 0 && y == 0 && z == 0) continue;
						int res = 0;
						if (x > 0) {
							int down = sum[0] + sum[1] - (x - 1) + y;
							int up = sum[0] - (x - 1);
							if (up >= 0 && down > 0)
								res = (res + 1LL * dp[x - 1][y][z] * up % mod * quick(down, mod - 2) % mod) % mod;
						}
						if (y > 0) {
							int down = sum[0] + sum[1] - x + y - 1;
							int up = sum[1] + y - 1 - (w[i] + z);
							if (up >= 0 && down > 0)
								res = (res + 1LL * dp[x][y - 1][z] * up % mod * quick(down, mod - 2) % mod) % mod;
						}
						if (y > 0 && z > 0) {
							int down = sum[0] + sum[1] - x + y - 1;
							int up = w[i] + (z - 1);
							if (up >= 0 && down > 0)
								res = (res + 1LL * dp[x][y - 1][z - 1] * up % mod * quick(down, mod - 2) % mod) % mod;
						}
						dp[x][y][z] = res;
						if (x + y == m) {
							int val = w[i] + z;
							ans[i] = (ans[i] + 1LL * val * dp[x][y][z] % mod) % mod;
						}
					}
				}
			}
		}
	}
	for (int i = 1; i <= n; i++) {
		cout << ans[i] << '\n';
	}
	return 0;
}