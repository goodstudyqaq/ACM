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
	int n, q;
	cin >> n >> q;
	string s;
	cin >> s;
	vector< vector< int > > nxt(n, vector< int >(26, n));

	for (int i = n - 1; i >= 0; i--) {
		if (i != n - 1) {
			for (int j = 0; j < 26; j++) {
				nxt[i][j] = nxt[i + 1][j];
			}
		}
		nxt[i][s[i] - 'a'] = i;
	}
	vector< vector< vector< int > > > dp(255, vector< vector< int > >(255, vector< int >(255, n + 10)));
	dp[0][0][0] = 0;
	int sz[3] = { 0 };
	string A[3];
	A[0].resize(255), A[1].resize(255), A[2].resize(255);
	while (q--) {
		char a, c;
		int idx;
		cin >> a >> idx;
		idx--;
		if (a == '+') {
			cin >> c;
			A[idx][++sz[idx]] = c;
			int beg[3] = { 0 };
			beg[idx] = sz[idx];
			for (int i = beg[0]; i <= sz[0]; i++) {
				for (int j = beg[1]; j <= sz[1]; j++) {
					for (int k = beg[2]; k <= sz[2]; k++) {
						dp[i][j][k] = n + 10;
						int val;
						if (i - 1 >= 0) {
							val = dp[i - 1][j][k];
							if (val < n && nxt[val][A[0][i] - 'a'] != n) {
								dp[i][j][k] = min(dp[i][j][k], nxt[val][A[0][i] - 'a'] + 1);
							}
						}
						if (j - 1 >= 0) {
							val = dp[i][j - 1][k];
							if (val < n && nxt[val][A[1][j] - 'a'] != n) {
								dp[i][j][k] = min(dp[i][j][k], nxt[val][A[1][j] - 'a'] + 1);
							}
						}
						if (k - 1 >= 0) {
							val = dp[i][j][k - 1];
							if (val < n && nxt[val][A[2][k] - 'a'] != n) {
								dp[i][j][k] = min(dp[i][j][k], nxt[val][A[2][k] - 'a'] + 1);
							}
						}
					}
				}
			}
		} else {
			sz[idx]--;
		}
		int val = dp[sz[0]][sz[1]][sz[2]];
		// debug(q, val);
		if (val == n + 10) {
			cout << "NO" << endl;
		} else {
			cout << "YES" << endl;
		}
	}
	return 0;
}