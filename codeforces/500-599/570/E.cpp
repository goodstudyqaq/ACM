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
typedef pair< int, int > pii;

const int mod = 1e9 + 7;
int dir[4][2] = { 0, -1, -1, 0, 1, 0, 0, 1 };

int main() {
#ifdef LOCAL
	freopen("data.in", "r", stdin);
#endif
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n, m;
	cin >> n >> m;
	vector< string > mp;
	mp.resize(n + 1);
	for (int i = 1; i <= n; i++) {
		string s;
		cin >> s;
		mp[i] = " " + s;
	}

	int len = n + m - 1;

	vector< vector< vector< int > > > dp(2, vector< vector< int > >(n + 1, vector< int >(n + 1, 0)));
	debug(len);

	for (int i = (len - 1) / 2; i >= 0; i--) {
		debug(i);

		// 特判最开始的地方
		if (i == (len - 1) / 2) {
			if (len % 2) {
				// 需要相等
				// x1 + y1 == i
				for (int x1 = max(0, i - (m - 1)); x1 <= n - 1 && x1 <= i; x1++) {
					dp[i % 2][x1 + 1][x1 + 1] = 1;
				}
			} else {
				// 位置差不能超过1
				for (int x1 = max(0, i - (m - 1)); x1 <= i && x1 <= n - 1; x1++) {
					int thex = x1 + 1;
					int they = i - x1 + 1;

					if (they + 1 <= m && mp[thex][they] == mp[thex][they + 1]) {
						dp[i % 2][x1 + 1][x1 + 1] = 1;
					}
					if (thex + 1 <= n && mp[thex][they] == mp[thex + 1][they]) {
						dp[i % 2][x1 + 1][x1 + 2] = 1;
					}
				}
			}
		} else {
			for (int x1 = max(0, i - (m - 1)); x1 <= i && x1 <= n - 1; x1++) {
				int oi = n + m - 2 - i;
				for (int x2 = max(0, oi - (m - 1)); x2 <= oi && x2 <= n - 1; x2++) {
					dp[i % 2][x1 + 1][x2 + 1] = 0;
					int thex = x1 + 1;
					int they = i - x1 + 1;
					int otherx = x2 + 1;
					int othery = oi - x2 + 1;
					// debug(thex, they, otherx, othery);
					// debug(x1, x2);
					if (mp[thex][they] == mp[otherx][othery]) {
						for (int k1 = 2; k1 < 4; k1++) {
							int tmpx1 = thex + dir[k1][0];
							int tmpy1 = they + dir[k1][1];
							if (tmpx1 >= 1 && tmpx1 <= n && tmpy1 >= 1 && tmpy1 <= m)
								for (int k2 = 0; k2 < 2; k2++) {
									int tmpx2 = otherx + dir[k2][0];
									int tmpy2 = othery + dir[k2][1];
									// debug(tmpx1, tmpy1, tmpx2, tmpy2);
									if (tmpx2 >= 1 && tmpx2 <= n && tmpy2 >= 1 && tmpy2 <= m) {
										(dp[i % 2][x1 + 1][x2 + 1] += dp[(i + 1) % 2][tmpx1][tmpx2]) %= mod;
										// debug(dp[i % 2][x1 + 1][x2 + 1]);
									}
								}
						}
					}
				}
			}
		}
	}

	cout << dp[0][1][n] << '\n';
	return 0;
}