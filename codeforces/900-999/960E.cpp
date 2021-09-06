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
vector< int > value;
vector< vector< int > > V;
// 0 表示乘 1 的和，1 表示乘 -1 的和
vector< int > dp, sz;

void dfs1(int u, int pre) {
	sz[u] = 1;
	for (auto it : V[u]) {
		if (it == pre) continue;
		dfs1(it, u);
		sz[u] += sz[it];
		dp[u] = (dp[u] - dp[it]) % mod;
	}
	dp[u] = (dp[u] + 1LL * sz[u] * value[u] % mod) % mod;
}
int ans;

void dfs2(int u, int pre) {
	debug(u, dp[u]);
	ans = (ans + dp[u]) % mod;
	debug(ans);
	for (auto v : V[u]) {
		if (v == pre) continue;

		// 换根
		int du = dp[u], dv = dp[v];
		int su = sz[u], sv = sz[v];

		sz[u] -= sz[v];
		dp[u] = (dp[u] + dp[v]) % mod;
		dp[u] = (dp[u] - 1LL * sz[v] * value[u] % mod) % mod;
		sz[v] += sz[u];
		dp[v] = (dp[v] - dp[u]) % mod;
		dp[v] = (dp[v] + 1LL * sz[u] * value[v] % mod) % mod;
		dfs2(v, u);

		dp[u] = du;
		dp[v] = dv;
		sz[u] = su;
		sz[v] = sv;
	}
}

int main() {
#ifdef LOCAL
	freopen("data.in", "r", stdin);
#endif
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n;
	cin >> n;
	value.resize(n + 1);
	V.resize(n + 1);
	dp.resize(n + 1);
	sz.resize(n + 1);
	for (int i = 1; i <= n; i++) {
		cin >> value[i];
	}
	for (int i = 1; i < n; i++) {
		int u, v;
		cin >> u >> v;
		V[u].push_back(v);
		V[v].push_back(u);
	}
	dfs1(1, 0);

	for (int i = 1; i <= n; i++) {
		debug(i, dp[i]);
	}

	dfs2(1, 0);
	ans = (ans + mod) % mod;
	cout << ans << endl;
	return 0;
}