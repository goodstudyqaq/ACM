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

string s, p;
int get_last_idx(int idx) {
	int now = idx;
	for (int i = p.size() - 1; i >= 0; i--) {
		while (now >= 0 && s[now] != p[i]) now--;
		if (now == -1) return -1;
		if (i == 0) {
			return now;
		}
		now--;
	}
}
const int inf = 1000;

int main() {
#ifdef LOCAL
	freopen("data.in", "r", stdin);
#endif
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> s >> p;
	vector< int > last(s.size(), -1);
	for (int i = p.size() - 1; i < s.size(); i++) {
		int last_idx = get_last_idx(i);
		last[i] = last_idx;
	}

	for (int i = 0; i < s.size(); i++) {
		debug(i, last[i]);
	}

	vector< vector< int > > dp(s.size() + 1, vector< int >(s.size() + 1, -inf));
	dp[0][0] = 0;
	for (int i = 1; i <= s.size(); i++) {
		for (int j = 0; j <= i; j++) {
			dp[i][j] = 0;
			dp[i][j] = dp[i - 1][j];
			if (j - 1 >= 0)
				// dp[i][j] = dp[i - 1][j - 1];
				dp[i][j] = max(dp[i - 1][j - 1], dp[i][j]);
			int s_idx = i - 1;
			int last_idx = last[s_idx];
			if (last_idx != -1) {
				int del_num = i - last_idx - p.size();
				if (del_num <= j) {
					dp[i][j] = max(dp[i][j], dp[last_idx][j - del_num] + 1);
				}
			}
			// debug(i, j, dp[i][j]);
		}
	}
	for (int i = 0; i <= s.size(); i++) {
		cout << dp[s.size()][i] << " ";
	}
	cout << endl;
	return 0;
}