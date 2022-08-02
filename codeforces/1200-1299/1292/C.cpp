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

vector< vector< int > > sz, fa;

void dfs(int u, int pre, int rt) {
	sz[rt][u] = 1;
	fa[rt][u] = pre;
	for (auto it : V[u]) {
		if (it == pre) continue;
		dfs(it, u, rt);
		sz[rt][u] += sz[rt][it];
	}
}

vector< vector< long long > > dp;
long long dfs2(int u, int v) {
	if (dp[u][v] != -1) {
		return dp[u][v];
	}
	long long res = sz[u][v] * sz[v][u];
	for (auto it : V[v]) {
		if (it == fa[u][v]) continue;
		res = max(res, dfs2(u, it) + sz[u][v] * sz[v][u]);
	}
	for (auto it : V[u]) {
		if (it == fa[v][u]) continue;
		res = max(res, dfs2(v, it) + sz[u][v] * sz[v][u]);
	}
	return dp[u][v] = dp[v][u] = res;
}

int main() {
#ifdef LOCAL
	freopen("data.in", "r", stdin);
#endif
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n;
	cin >> n;
	V.resize(n + 1);
	sz.resize(n + 1, vector< int >(n + 1, 0));
	fa.resize(n + 1, vector< int >(n + 1, -1));
	dp.resize(n + 1, vector< long long >(n + 1, -1));
	for (int i = 1; i < n; i++) {
		int u, v;
		cin >> u >> v;
		V[u].push_back(v);
		V[v].push_back(u);
	}

	for (int i = 1; i <= n; i++) {
		dfs(i, -1, i);
	}

	long long ans = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = i + 1; j <= n; j++) {
			// int val = dfs2(i, j);
			// debug(i, j, val);
			ans = max(ans, dfs2(i, j));
		}
	}
	cout << ans << endl;
	return 0;
}