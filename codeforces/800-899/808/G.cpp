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

void kmp_pre(string& x, vector< int >& next) {
	int m = x.size();
	next.resize(m + 1);
	int i, j;
	j = next[0] = -1;
	i = 0;
	while (i < m) {
		while (j != -1 && x[i] != x[j]) j = next[j];
		if (x[++i] == x[++j])
			next[i] = next[j];
		else
			next[i] = j;
	}
}

int main() {
#ifdef LOCAL
	freopen("data.in", "r", stdin);
#endif
	ios::sync_with_stdio(false);
	cin.tie(0);
	string s, t;
	cin >> s >> t;
	int s_len = s.size();
	int t_len = t.size();
	vector< int > next;
	kmp_pre(t, next);

	// dp[i][j] = s 串长度为 i 时的后缀与 t 的前缀匹配的长度为 j 时的最大价值
	vector< vector< int > > dp(s_len + 1, vector< int >(t_len + 1, -1));
	dp[0][0] = 0;

	for (int i = 0; i < s_len; i++) {
		for (int j = 0; j <= t_len; j++) {
			if (dp[i][j] == -1) continue;
			char it = s[i];
			if (it == '?') {
				for (int k = 0; k < 26; k++) {
					int tmp = dp[i][j];
					int now = j;
					while (now != -1 && t[now] - 'a' != k) now = next[now];
					now++;
					if (now >= t_len) tmp++;
					dp[i + 1][now] = max(dp[i + 1][now], tmp);
				}
			} else {
				int now = j;
				while (now != -1 && t[now] != s[i]) now = next[now];
				now++;
				int tmp = dp[i][j];
				if (now >= t_len) tmp++;
				dp[i + 1][now] = max(dp[i + 1][now], tmp);
			}
		}
	}

	int res = 0;
	for (int i = 0; i <= t_len; i++) {
		res = max(res, dp[s_len][i]);
	}
	cout << res << endl;
	return 0;
}