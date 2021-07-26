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

string s;
int m;
vector< vector< vector< int > > > sum;
bool check(int now_len) {
	int f = now_len % 2;
	int tmp = m % 2;

	int other_len = now_len - m;
	if (sum[now_len][f][tmp ^ 1] - sum[other_len][f][tmp ^ 1] > 0) {
		return false;
	}
	if (sum[now_len][f ^ 1][tmp] - sum[other_len][f ^ 1][tmp] > 0) {
		return false;
	}
	return true;
}

int main() {
#ifdef LOCAL
	freopen("data.in", "r", stdin);
#endif
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n;
	cin >> n;
	cin >> s;
	cin >> m;

	sum.resize(n + 1, vector< vector< int > >(2, vector< int >(3, 0)));
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j < 3; j++) {
			sum[i][0][j] = sum[i - 1][0][j];
			sum[i][1][j] = sum[i - 1][1][j];
		}
		if (s[i - 1] == 'b') {
			sum[i][i % 2][0]++;
		} else if (s[i - 1] == 'a') {
			sum[i][i % 2][1]++;
		} else {
			sum[i][i % 2][2]++;
		}
	}

	vector< int > dp(n + 1, 0);
	vector< int > mi(n + 1, 0);
	mi[0] = 0;
	for (int i = m; i <= n; i++) {
		dp[i] = dp[i - 1];
		mi[i] = mi[i - 1];

		if (check(i)) {
			if (dp[i] < dp[i - m] + 1) {
				dp[i] = dp[i - m] + 1;
				mi[i] = mi[i - m] + sum[i][0][2] - sum[i - m][0][2] + sum[i][1][2] - sum[i - m][1][2];
			} else if (dp[i] == dp[i - m] + 1) {
				int val = mi[i - m] + sum[i][0][2] - sum[i - m][0][2] + sum[i][1][2] - sum[i - m][1][2];
				if (mi[i] > val) {
					mi[i] = val;
				}
			}
		}
		debug(i, dp[i], mi[i]);
	}
	cout << mi[n] << endl;
	return 0;
}