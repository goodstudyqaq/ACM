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

vector< int > nxt;
void kmp_pre(string& x) {
	nxt.resize(x.size() + 1);
	int i, j;
	j = nxt[0] = -1;
	i = 0;
	int m = x.size();
	while (i < m) {
		while (j != -1 && (j >= x.size() || x[i] != x[j])) j = nxt[j];
		nxt[++i] = ++j;
	}
}

int main() {
#ifdef LOCAL
	freopen("data.in", "r", stdin);
#endif
	ios::sync_with_stdio(false);
	cin.tie(0);
	string s1, s2, s3;
	cin >> s1 >> s2 >> s3;
	kmp_pre(s3);
	int s1_len = s1.size(), s2_len = s2.size(), s3_len = s3.size();
	vector< vector< vector< int > > > dp(s1_len + 1, vector< vector< int > >(s2_len + 1, vector< int >(s3_len + 1, -1)));
	vector< vector< vector< array< int, 3 > > > > pre(s1_len + 1, vector< vector< array< int, 3 > > >(s2_len + 1, vector< array< int, 3 > >(s3_len + 1, { 0, 0, 0 })));

	for (int i = 0; i <= s1_len; i++) {
		dp[i][0][0] = 0;
	}
	for (int i = 0; i <= s2_len; i++) {
		dp[0][i][0] = 0;
	}

	function< void(int, int, int, int, int, int, int) > Compare = [&](int i1, int j1, int k1, int i2, int j2, int k2, int val) {
		if (dp[i1][j1][k1] < dp[i2][j2][k2] + val) {
			dp[i1][j1][k1] = dp[i2][j2][k2] + val;
			pre[i1][j1][k1] = { i2, j2, k2 };
		}
	};
	for (int i = 0; i <= s1_len; i++) {
		for (int j = 0; j <= s2_len; j++) {
			for (int k = 0; k <= s3_len; k++) {
				if (dp[i][j][k] == -1) continue;
				// debug(i, j, k, dp[i][j][k]);
				if (i + 1 <= s1_len) {
					Compare(i + 1, j, k, i, j, k, 0);
				}
				if (j + 1 <= s2_len) {
					Compare(i, j + 1, k, i, j, k, 0);
				}

				if (i + 1 <= s1_len && j + 1 <= s2_len) {
					if (s1[i] == s2[j]) {
						int p = k;
						while (p != -1 && p != s3_len && s3[p] != s1[i]) {
							p = nxt[p];
						}
						p++;
						Compare(i + 1, j + 1, p, i, j, k, 1);
					}
				}
			}
		}
	}

	int mx = -1;
	int chosek = -1;
	for (int i = 0; i <= s3_len - 1; i++) {
		if (mx < dp[s1_len][s2_len][i]) {
			mx = dp[s1_len][s2_len][i];
			chosek = i;
		}
	}
	debug(mx, chosek);
	if (mx <= 0) {
		puts("0");
		return 0;
	}
	array< int, 3 > now = { s1_len, s2_len, chosek };
	string ans = "";
	while (dp[now[0]][now[1]][now[2]]) {
		auto lxt = pre[now[0]][now[1]][now[2]];
		if (dp[lxt[0]][lxt[1]][lxt[2]] + 1 == dp[now[0]][now[1]][now[2]]) {
			ans += s1[now[0] - 1];
		}
		now = lxt;
	}
	reverse(ans.begin(), ans.end());
	cout << ans << endl;
	return 0;
}