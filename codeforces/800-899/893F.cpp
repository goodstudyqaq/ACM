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
vector< int > a;
vector< vector< int > > V;
int n, r;

vector< int > dfn, sz, dep;
int now_dfn;
int mx_dep;
void dfs(int u, int pre, int d) {
	dfn[u] = ++now_dfn;
	sz[u] = 1;
	dep[u] = d;
	mx_dep = max(mx_dep, dep[u]);
	for (auto it : V[u]) {
		if (it == pre) continue;
		dfs(it, u, d + 1);
		sz[u] += sz[it];
	}
}

//

const int maxn = 1e5 + 5;
int mi[maxn * 40];
int son[maxn * 40][2];
int ncnt;
int root[maxn];

void push_up(int rt) {
	mi[rt] = min(mi[son[rt][0]], mi[son[rt][1]]);
}

void build(int l, int r, int now) {
	if (l == r) {
		mi[now] = 1e9 + 1;
		return;
	}
	int m = l + r >> 1;
	son[now][0] = ++ncnt;
	son[now][1] = ++ncnt;
	build(l, m, son[now][0]);
	build(m + 1, r, son[now][1]);
	push_up(now);
}

void update(int L, int val, int l, int r, int now_rt, int pre_rt) {
	if (l == r) {
		mi[now_rt] = val;
		return;
	}
	int m = l + r >> 1;
	if (L <= m) {
		son[now_rt][1] = son[pre_rt][1];
		son[now_rt][0] = ++ncnt;
		update(L, val, l, m, son[now_rt][0], son[pre_rt][0]);
	} else {
		son[now_rt][0] = son[pre_rt][0];
		son[now_rt][1] = ++ncnt;
		update(L, val, m + 1, r, son[now_rt][1], son[pre_rt][1]);
	}
	push_up(now_rt);
}

int query(int L, int R, int l, int r, int rt) {
	if (L <= l && r <= R) {
		return mi[rt];
	}
	int m = l + r >> 1;
	int res = 1e9 + 1;
	if (L <= m) {
		res = min(res, query(L, R, l, m, son[rt][0]));
	}
	if (R > m) {
		res = min(res, query(L, R, m + 1, r, son[rt][1]));
	}
	return res;
}

//

void bfs() {
	queue< int > Q;
	Q.push(r);
	int lxt_rt = root[0];
	while (!Q.empty()) {
		int x = Q.front();
		Q.pop();
		int x_dep = dep[x];
		root[x_dep] = ++ncnt;
		update(dfn[x], a[x], 1, n, root[x_dep], lxt_rt);
		lxt_rt = root[x_dep];
		for (auto it : V[x]) {
			if (dep[it] != dep[x] + 1) continue;
			Q.push(it);
		}
	}
}

int main() {
#ifdef LOCAL
	freopen("data.in", "r", stdin);
#endif
	ios::sync_with_stdio(false);
	cin.tie(0);

	cin >> n >> r;
	a.resize(n + 1);
	V.resize(n + 1);
	dfn.resize(n + 1);
	sz.resize(n + 1);
	dep.resize(n + 1);
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
	}

	for (int i = 1; i < n; i++) {
		int u, v;
		cin >> u >> v;
		V[u].push_back(v);
		V[v].push_back(u);
	}

	// 得到 dfs 序 d 从 1 开始
	dfs(r, -1, 1);

	// 初始化
	root[0] = ++ncnt;
	build(1, n, root[0]);

	bfs();

	int m;
	cin >> m;
	int lxt = 0;
	while (m--) {
		int p, q;
		cin >> p >> q;
		int x = (p + lxt) % n + 1;
		int k = (q + lxt) % n;
		int x_dep = dep[x];
		int ask_dep = min(mx_dep, x_dep + k);
		int L = dfn[x];
		int R = L + sz[x] - 1;
		int res = query(L, R, 1, n, root[ask_dep]);
		lxt = res;
		cout << res << '\n';
	}
	return 0;
}