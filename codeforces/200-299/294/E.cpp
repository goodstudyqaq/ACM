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

typedef pair< int, int > pii;
vector< vector< pii > > V;

vector< int > fa, weight;
void dfs(int u, int pre) {
	for (auto e : V[u]) {
		int v = e.first, w = e.second;
		if (v != pre) {
			fa[v] = u;
			weight[v] = w;
			dfs(v, u);
		}
	}
}

vector< long long > sum, real_sum;
vector< int > sz;
void dfs1(int u) {
	sum[u] = 0;
	sz[u] = 1;
	for (auto e : V[u]) {
		int v = e.first, w = e.second;
		if (fa[v] == u) {
			dfs1(v);
			sz[u] += sz[v];
			sum[u] += sum[v] + 1LL * sz[v] * w;
		}
	}
}

void dfs2(int u) {
	real_sum[u] = sum[u];
	for (auto e : V[u]) {
		int v = e.first, w = e.second;
		if (fa[v] == u) {
			// 换根
			long long sum_u = sum[u], sum_v = sum[v];
			int sz_u = sz[u], sz_v = sz[v];

			sum[u] = sum[u] - sum[v] - 1LL * sz[v] * w;
			sz[u] -= sz[v];

			sum[v] += sum[u] + 1LL * sz[u] * w;
			sz[v] += sz[u];
			dfs2(v);

			sum[u] = sum_u;
			sum[v] = sum_v;
			sz[u] = sz_u;
			sz[v] = sz_v;
		}
	}
}

int dfs3(int u) {
	int res = u;
	for (auto e : V[u]) {
		int v = e.first, w = e.second;
		if (fa[v] == u) {
			int idx = dfs3(v);
			if (real_sum[res] > real_sum[idx]) {
				res = idx;
			}
		}
	}
	return res;
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
	fa.resize(n + 1);
	weight.resize(n + 1);
	sum.resize(n + 1);
	real_sum.resize(n + 1);
	sz.resize(n + 1);
	for (int i = 1; i < n; i++) {
		int u, v, w;
		cin >> u >> v >> w;
		V[u].push_back({ v, w });
		V[v].push_back({ u, w });
	}
	dfs(1, 0);

	long long ans = 1e18;
	for (int i = 2; i <= n; i++) {
		int father = fa[i];
		int w = weight[i];
		debug(i, father, w);

		// 砍掉 i father 这条边

		fa[i] = 0;
		dfs1(1);
		dfs1(i);
		dfs2(1);
		dfs2(i);
		int u = dfs3(1), v = dfs3(i);

		long long sum_u = real_sum[u], sum_v = real_sum[v];

		int sz_u = sz[1], sz_v = sz[i];
		debug(u, v, sum_u, sum_v, sz_u, sz_v);

		long long tmp = 1LL * sz_u * sz_v * w + sum_u * sz_v + sum_v * sz_u;
		long long tmp2 = 0;

		for (int j = 1; j <= n; j++) {
			tmp2 += real_sum[j];
		}
		debug(tmp, tmp2);
		if (ans > tmp + tmp2 / 2) {
			ans = tmp + tmp2 / 2;
		}
		fa[i] = father;
	}
	cout << ans << endl;
	return 0;
}