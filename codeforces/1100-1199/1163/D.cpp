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

const int inf = 2000;

void kmp(string& x, vector< int >& next) {
	int i, j;
	int m = x.size();
	next.resize(m + 1);
	j = next[0] = -1;
	i = 0;
	while (i < m) {
		while (j != -1 && x[i] != x[j]) j = next[j];
		next[++i] = ++j;
	}
}

int main() {
#ifdef LOCAL
	freopen("data.in", "r", stdin);
#endif
	ios::sync_with_stdio(false);
	cin.tie(0);
	string c, s, t;
	cin >> c >> s >> t;
	vector< int > next_s, next_t;
	kmp(s, next_s);
	kmp(t, next_t);
	vector< vector< vector< int > > > dp(c.size() + 1, vector< vector< int > >(s.size() + 1, vector< int >(t.size() + 1, -inf)));
	dp[0][0][0] = 0;
	for (int i = 0; i < c.size(); i++) {
		for (int j = 0; j <= min(i, ( int )s.size()); j++) {
			for (int k = 0; k <= min(i, ( int )t.size()); k++) {
				if (dp[i][j][k] == -inf) continue;
				// debug(i, j, k, dp[i][j][k]);
				if (c[i] == '*') {
					for (char it = 'a'; it <= 'z'; it++) {
						int posj = j;
						while (posj != -1 && it != s[posj]) {
							posj = next_s[posj];
						}
						posj++;

						int posk = k;
						while (posk != -1 && it != t[posk]) {
							posk = next_t[posk];
						}
						posk++;
						int cnt = 0;
						if (posj == s.size()) cnt++;
						if (posk == t.size()) cnt--;
						dp[i + 1][posj][posk] = max(dp[i + 1][posj][posk], dp[i][j][k] + cnt);
					}

				} else {
					int posj = j;
					while (posj != -1 && c[i] != s[posj]) {
						posj = next_s[posj];
					}
					posj++;

					int posk = k;
					while (posk != -1 && c[i] != t[posk]) {
						posk = next_t[posk];
					}
					posk++;
					int cnt = 0;
					if (posj == s.size()) cnt++;
					if (posk == t.size()) cnt--;
					dp[i + 1][posj][posk] = max(dp[i + 1][posj][posk], dp[i][j][k] + cnt);
				}
			}
		}
	}
	int ans = -inf;
	for (int i = 0; i <= s.size(); i++) {
		for (int j = 0; j <= t.size(); j++) {
			ans = max(ans, dp[c.size()][i][j]);
		}
	}
	cout << ans << endl;
	return 0;
}