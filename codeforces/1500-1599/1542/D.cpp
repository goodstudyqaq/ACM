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

struct Node {
	char f;
	int val;
};
typedef pair< int, int > pii;

const int mod = 998244353;
int main() {
#ifdef LOCAL
	freopen("data.in", "r", stdin);
#endif
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n;
	cin >> n;
	vector< Node > a(n + 1);
	for (int i = 1; i <= n; i++) {
		cin >> a[i].f;
		if (a[i].f == '+') {
			cin >> a[i].val;
		}
	}

	long long ans = 0;
	for (int i = 1; i <= n; i++) {
		if (a[i].f == '+') {
			vector< long long > dp(n, 0);
			dp[0] = 1;
			pii it = { a[i].val, i };
			for (int j = 1; j <= n; j++) {
				if (a[j].f == '-') {
					for (int k = 0; k < n - 1; k++) {
						if (k == 0 && j < i) {
							long long tmp = (dp[k] * 2 % mod + dp[k + 1]) % mod;
							dp[k] = tmp;
						} else {
							(dp[k] += dp[k + 1]) %= mod;
						}

						// long long tmp = (dp[k] + dp[k + 1]) % mod;
						// dp[k] = (dp[k] + tmp) % mod;
						// }
					}
				} else {
					pii it2 = { a[j].val, j };
					if (it2 > it) {
						for (int k = 0; k < n; k++) {
							dp[k] = dp[k] * 2 % mod;
						}
					} else if (it2 < it) {
						for (int k = n - 1; k > 0; k--) {
							(dp[k] += dp[k - 1]) %= mod;
						}
					}
				}
			}

			long long tmp = 0;
			for (int j = 0; j < n; j++) {
				debug(i, a[i].val, j, dp[j]);
				tmp = (tmp + dp[j]) % mod;
			}
			ans = (ans + tmp * a[i].val % mod) % mod;
		}
	}
	cout << ans << endl;
	return 0;
}