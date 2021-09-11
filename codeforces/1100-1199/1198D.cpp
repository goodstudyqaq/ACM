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

const int maxn = 51;
vector< string > mp;
int dp[maxn][maxn][maxn][maxn];
int sum[maxn][maxn];

int get_sum(int x1, int y1, int x2, int y2) {
	return sum[x2][y2] - sum[x1 - 1][y2] - sum[x2][y1 - 1] + sum[x1 - 1][y1 - 1];
}

int dfs(int x1, int y1, int x2, int y2) {

	if (x1 == x2 && y1 == y2) {
		return mp[x1][y1] == '#';
	}
	if (dp[x1][y1][x2][y2] != -1) return dp[x1][y1][x2][y2];

	int x = x2 - x1 + 1;
	int y = y2 - y1 + 1;
	int mx = max(x, y);

	for (int i = x1; i < x2; i++) {
		int tmp = dfs(x1, y1, i, y2) + dfs(i + 1, y1, x2, y2);
		mx = min(mx, tmp);
	}

	for (int i = y1; i < y2; i++) {
		int tmp = dfs(x1, y1, x2, i) + dfs(x1, i + 1, x2, y2);
		mx = min(mx, tmp);
	}

	// if (x >= y) {
	// 	for (int i = x1; i <= x2; i++) {
	// 		int tmp = get_sum(i, y1, i, y2);
	// 		if (tmp == 0) {
	// 			mx = min(mx, dfs())
	// 		}
	// 	}
	// } else {
	// 	int empty = 0;
	// 	for (int i = y1; i <= y2; i++) {
	// 		int tmp = get_sum(x1, i, x2, i);
	// 		if (tmp == 0) empty++;
	// 	}
	// 	mx = min(mx, y - empty);
	// }
	return dp[x1][y1][x2][y2] = mx;
}

int main() {
#ifdef LOCAL
	freopen("data.in", "r", stdin);
#endif
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n;
	cin >> n;
	mp.resize(n + 1);
	for (int i = 1; i <= n; i++) {
		string s;
		cin >> s;
		mp[i] = " " + s;
	}

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			sum[i][j] += sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] + (mp[i][j] == '#');
		}
	}
	memset(dp, -1, sizeof(dp));

	cout << dfs(1, 1, n, n) << endl;
	return 0;
}