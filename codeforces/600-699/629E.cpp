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

vector< vector< int > > V;

vector< int > dep, sz;
vector< vector< int > > fa;
vector< long long > dp, dp2;
void dfs(int u, int pre, int d) {
	fa[u][0] = pre;
	sz[u] = 1;
	dep[u] = d;
	for (auto v : V[u]) {
		if (v == pre) continue;
		dfs(v, u, d + 1);
		dp[u] += dp[v] + sz[v];
		sz[u] += sz[v];
	}
}

void dfs2(int u, int pre) {
	dp2[u] = dp[u];
	for (auto v : V[u]) {
		if (v == pre) continue;
		// 换根
		long long d1 = dp[u], d2 = dp[v];
		int sz1 = sz[u], sz2 = sz[v];

		dp[u] = dp[u] - dp[v] - sz[v];
		sz[u] = sz[u] - sz[v];
		dp[v] = dp[v] + dp[u] + sz[u];
		sz[v] = sz[v] + sz[u];
		dfs2(v, u);
		dp[u] = d1;
		dp[v] = d2;
		sz[u] = sz1;
		sz[v] = sz2;
	}
}

int n, m;

void init() {
	for (int j = 1; j < 17; j++) {
		for (int i = 1; i <= n; i++) {
			int go = fa[i][j - 1];
			fa[i][j] = fa[go][j - 1];
		}
	}
}

int query(int x, int y) {
	if (dep[x] > dep[y]) swap(x, y);
	for (int j = 16; j >= 0 && dep[x] != dep[y]; j--) {
		if (dep[y] - (1 << j) < dep[x]) continue;
		y = fa[y][j];
	}
	if (x == y) return x;
	for (int j = 16; j >= 0; j--) {
		if (dep[x] - (1 << j) < 0 || fa[x][j] == fa[y][j]) continue;
		x = fa[x][j], y = fa[y][j];
	}
	return fa[x][0];
}

int query2(int u, int dis) {
	for (int j = 16; j >= 0; j--) {
		if ((dis >> j) & 1) {
			u = fa[u][j];
		}
	}
	return u;
}

double work(int u, int v) {
	if (dep[u] > dep[v]) swap(u, v);  // u 在上面
	int father = query(u, v);
	if (father == u) {
		int dis = dep[v] - dep[u];
		int sub_father = query2(v, dis - 1);
		long long down = 1LL * (n - sz[sub_father]) * sz[v];

		long long d1 = dp2[u], d2 = dp[sub_father];
		int sz2 = sz[sub_father];

		d1 = d1 - d2 - sz2;

		long long up = dp[v] * (n - sz[sub_father]) + 1LL * sz[v] * d1;
		// debug(u, v, up, down, d1, d2);
		return 1.0 * up / (1.0 * down) + dis + 1;

	} else {
		long long down = 1LL * sz[u] * sz[v];
		int dis = dep[u] + dep[v] - 2 * dep[father];
		long long up = dp[v] * sz[u] + dp[u] * sz[v];
		return 1.0 * up / (1.0 * down) + dis + 1;
	}
}

int main() {
#ifdef LOCAL
	freopen("data.in", "r", stdin);
#endif
	ios::sync_with_stdio(false);
	cin.tie(0);

	cin >> n >> m;
	V.resize(n + 1);
	dep.resize(n + 1);
	sz.resize(n + 1);
	fa.resize(n + 1, vector< int >(17, 0));
	dp.resize(n + 1, 0);
	dp2.resize(n + 1, 0);
	for (int i = 1; i < n; i++) {
		int u, v;
		cin >> u >> v;
		V[u].push_back(v);
		V[v].push_back(u);
	}
	dfs(1, 0, 1);
	dfs2(1, 0);
	init();
	cout << fixed << setprecision(8);
	for (int i = 1; i <= m; i++) {
		int u, v;
		cin >> u >> v;
		cout << work(u, v) << '\n';
	}
	return 0;
}