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

const int mod = 1e9 + 7;
vector< string > mp;
int n, m;
vector< vector< int > > sum;

void init() {
	sum.resize(n + 1, vector< int >(m + 1, 0));
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			sum[i][j] = mp[i][j] == 'R';
			sum[i][j] += sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1];
		}
	}
}

int get_sum(int x1, int y1, int x2, int y2) {
	return sum[x2][y2] - sum[x1 - 1][y2] - sum[x2][y1 - 1] + sum[x1 - 1][y1 - 1];
}

vector< vector< long long > > sum2, sum3;
vector< vector< vector< long long > > > dp;

int get_idx(int i, int j) {
	int l = 1, r = i - 1;
	int ans = -1;
	int limit = n - i - get_sum(i + 1, j, n, j);
	while (l <= r) {
		int mid = l + r >> 1;
		int tmp = get_sum(mid + 1, j, i, j);
		if (tmp <= limit) {
			ans = mid;
			r = mid - 1;
		} else {
			l = mid + 1;
		}
	}
	return ans;
}

int get_idx2(int i, int j) {
	int l = 1, r = j - 1;
	int ans = -1;
	int limit = m - j - get_sum(i, j + 1, i, m);
	while (l <= r) {
		int mid = l + r >> 1;
		int tmp = get_sum(i, mid + 1, i, j);
		if (tmp <= limit) {
			ans = mid;
			r = mid - 1;
		} else {
			l = mid + 1;
		}
	}
	return ans;
}

int main() {
#ifdef LOCAL
	freopen("data.in", "r", stdin);
#endif
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n >> m;
	mp.resize(n + 1);
	for (int i = 1; i <= n; i++) {
		string s;
		cin >> s;
		mp[i] = " " + s;
	}

	if (n == m && n == 1) {
		if (mp[1][1] == 'R')
			cout << 0 << endl;
		else
			cout << 1 << endl;
		return 0;
	}

	init();
	sum2.resize(n + 1, vector< long long >(m + 1, 0));
	sum3.resize(n + 1, vector< long long >(m + 1, 0));
	dp.resize(n + 1, vector< vector< long long > >(m + 1, vector< long long >(2, 0)));
	// dp[i][j][0] 到 (i, j) 且最后一步是从左边来的
	// dp[i][j][1] 到 (i, j) 且最后一步是从上边来的

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (i == 1 && j == 1) {
				dp[i][j][0] = 1;
				dp[i][j][1] = 1;
				sum2[i][j] = 1;
				sum3[i][j] = 1;
				continue;
			}
			int idx1 = get_idx(i, j);
			if (idx1 != -1)
				dp[i][j][1] = (sum2[i - 1][j] - sum2[idx1 - 1][j]) % mod;
			int idx2 = get_idx2(i, j);
			if (idx2 != -1)
				dp[i][j][0] = (sum3[i][j - 1] - sum3[i][idx2 - 1]) % mod;
			sum2[i][j] = (sum2[i - 1][j] + dp[i][j][0]) % mod;
			sum3[i][j] = (sum3[i][j - 1] + dp[i][j][1]) % mod;
			debug(i, j, dp[i][j][0], dp[i][j][1]);
		}
	}

	long long res = ((dp[n][m][0] + dp[n][m][1]) % mod + mod) % mod;

	cout << res << endl;
	return 0;
}