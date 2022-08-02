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

int d[4][5][2] = { { { 0, 0 }, { 1, 0 }, { -1, 0 }, { 0, 1 }, { 0, 2 } }, { { 0, 0 }, { 1, 0 }, { -1, 0 }, { 0, -1 }, { 0, -2 } }, { { 0, 0 }, { 0, 1 }, { 0, -1 }, { 1, 0 }, { 2, 0 } }, { { 0, 0 }, { 0, 1 }, { 0, -1 }, { -1, 0 }, { -2, 0 } } };
int D[4][5][2] = { { { 0, 0 }, { 1, 0 }, { 2, 0 }, { 0, 1 }, { 0, -1 } },
	{ { 0, 0 }, { -1, 0 }, { -2, 0 }, { 0, 1 }, { 0, -1 } },
	{ { 0, 0 }, { 0, 1 }, { 0, 2 }, { 1, 0 }, { -1, 0 } },
	{ { 0, 0 }, { 0, -1 }, { 0, -2 }, { 1, 0 }, { -1, 0 } } };

char mp[10][10], ans[10][10];
int res;

int n, m;

bool ok(int x, int y) {
	if (x >= 0 && x < n && y >= 0 && y < m && mp[x][y] == '.') return true;
	return false;
}
void dfs(int cur) {
	if (cur > res) {
		res = cur;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				ans[i][j] = mp[i][j];
			}
		}
	}
	bool found = false;
	int cnt_found = 0;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (found) cnt_found++;
			if (cnt_found > 2) return;
			for (int k = 0; k < 4; k++) {
				bool f = true;
				for (int t = 0; t < 5; t++) {
					int tmpx = i + d[k][t][0];
					int tmpy = j + d[k][t][1];
					if (!ok(tmpx, tmpy)) {
						f = false;
						break;
					}
				}
				if (f) {
					found = true;
					for (int t = 0; t < 5; t++) {
						int tmpx = i + d[k][t][0];
						int tmpy = j + d[k][t][1];
						mp[tmpx][tmpy] = 'A' + cur;
					}
					dfs(cur + 1);
					for (int t = 0; t < 5; t++) {
						int tmpx = i + d[k][t][0];
						int tmpy = j + d[k][t][1];
						mp[tmpx][tmpy] = '.';
					}
				}
			}
		}
	}
}

int main() {
#ifdef LOCAL
	freopen("data.in", "r", stdin);
#endif
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n >> m;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			mp[i][j] = '.';
			ans[i][j] = '.';
		}
		mp[i][m] = '\0';
		ans[i][m] = '\0';
	}

	dfs(0);
	cout << res << endl;
	for (int i = 0; i < n; i++) {
		cout << ans[i] << endl;
	}
	return 0;
}