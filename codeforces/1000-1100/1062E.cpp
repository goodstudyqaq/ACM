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
vector< vector< int > > fa;

vector< int > in, dep;
int ncnt;
void dfs(int u, int d) {
	in[u] = ++ncnt;
	dep[u] = d;
	for (auto it : V[u]) {
		dfs(it, d + 1);
	}
}

int lca(int u, int v) {
	if (dep[u] > dep[v]) swap(u, v);
	for (int j = 16; j >= 0 && dep[u] != dep[v]; j--) {
		if (dep[v] - (1 << j) < dep[u]) continue;
		v = fa[v][j];
	}
	if (u == v) return u;
	for (int j = 16; j >= 0; j--) {
		if (dep[u] - (1 << j) < 0 || fa[u][j] == fa[v][j]) continue;
		u = fa[u][j], v = fa[v][j];
	}
	return fa[u][0];
}

int n, q;
vector< vector< int > > mx, mi, mx_idx, mi_idx;
void init() {
	// 预处理父亲
	for (int i = 1; i < 17; i++) {
		for (int j = 1; j <= n; j++) {
			int to = fa[j][i - 1];
			fa[j][i] = fa[to][i - 1];
		}
	}

	// 预处理区间最小值和最大值以及对应选择的下标
	for (int i = 1; i <= n; i++) {
		mx[i][0] = mi[i][0] = in[i];
		mx_idx[i][0] = mi_idx[i][0] = i;
	}

	for (int i = 1; i < 17; i++) {
		for (int j = 1; j <= n; j++) {
			int go = j + (1 << i) - 1;
			if (go > n) break;
			int to = j + (1 << (i - 1));
			if (mx[j][i - 1] > mx[to][i - 1]) {
				mx[j][i] = mx[j][i - 1];
				mx_idx[j][i] = mx_idx[j][i - 1];
			} else {
				mx[j][i] = mx[to][i - 1];
				mx_idx[j][i] = mx_idx[to][i - 1];
			}

			if (mi[j][i - 1] < mi[to][i - 1]) {
				mi[j][i] = mi[j][i - 1];
				mi_idx[j][i] = mi_idx[j][i - 1];
			} else {
				mi[j][i] = mi[to][i - 1];
				mi_idx[j][i] = mi_idx[to][i - 1];
			}
		}
	}
}

typedef pair< int, int > pii;
pii query(int l, int r) {
	int k = log2(r - l + 1);
	int mx_chose, mi_chose;
	if (mx[l][k] > mx[r - (1 << k) + 1][k]) {
		mx_chose = mx_idx[l][k];
	} else {
		mx_chose = mx_idx[r - (1 << k) + 1][k];
	}
	if (mi[l][k] < mi[r - (1 << k) + 1][k]) {
		mi_chose = mi_idx[l][k];
	} else {
		mi_chose = mi_idx[r - (1 << k) + 1][k];
	}
	return { mi_chose, mx_chose };
}
typedef pair< pii, int > piii;

piii work(int l, int r, int val) {
	pii res = { 0, -1 };
	int chose_idx;
	if (val == l || val == r) {
		pii tmp2;
		if (val == l) {
			tmp2 = query(l + 1, r);
		} else {
			tmp2 = query(l, r - 1);
		}
		int father = lca(tmp2.first, tmp2.second);
		int dep_father = dep[father];
		if (dep_father > res.second) {
			res.second = dep_father;
			res.first = val;
			chose_idx = father;
		}
	} else {
		pii tmp2 = query(l, val - 1);
		pii tmp3 = query(val + 1, r);
		int f1 = lca(tmp2.first, tmp2.second);
		int f2 = lca(tmp3.first, tmp3.second);
		int f3 = lca(f1, f2);
		int dep_father = dep[f3];
		if (dep_father > res.second) {
			res.second = dep_father;
			res.first = val;
			chose_idx = f3;
		}
	}
	return { res, chose_idx };
}

int main() {
#ifdef LOCAL
	freopen("data.in", "r", stdin);
#endif
	ios::sync_with_stdio(false);
	cin.tie(0);

	cin >> n >> q;

	V.resize(n + 1);
	fa.resize(n + 1, vector< int >(17, 0));
	in.resize(n + 1);
	dep.resize(n + 1);
	mx.resize(n + 1, vector< int >(17, 0));
	mi.resize(n + 1, vector< int >(17, 0));
	mx_idx.resize(n + 1, vector< int >(17, 0));
	mi_idx.resize(n + 1, vector< int >(17, 0));

	for (int i = 2; i <= n; i++) {
		int p;
		cin >> p;
		V[p].push_back(i);
		fa[i][0] = p;
	}
	dfs(1, 0);
	init();

	while (q--) {
		int l, r;
		cin >> l >> r;
		pii tmp = query(l, r);
		debug(tmp.first, tmp.second);

		piii res1 = work(l, r, tmp.first);
		piii res2 = work(l, r, tmp.second);
		if (res1.first.second > res2.first.second) {
			// debug(res1.first.first, res1.first.second, res1.second);
			cout << res1.first.first << ' ' << res1.first.second << '\n';
		} else {
			// debug(res2.first.first, res2.first.second, res2.second);
			cout << res2.first.first << ' ' << res2.first.second << '\n';
		}
	}
	return 0;
}