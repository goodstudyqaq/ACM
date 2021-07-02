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

const int maxn = 2e5 + 5;
struct Edge {
	int u, v, w, c, idx;
	bool operator<(const Edge& b) const {
		return w < b.w;
	}
} edges[maxn];
int f[maxn];
int find(int u) {
	return u == f[u] ? u : f[u] = find(f[u]);
}

vector< Edge > V[maxn];

int mx[maxn][20];
int idx[maxn][20];
int fa[maxn][20];
int dep[maxn];
void dfs(int u, int pre, int d) {
	dep[u] = d;
	fa[u][0] = pre;
	for (auto e : V[u]) {
		if (e.v == pre) continue;
		mx[e.v][0] = e.w;
		idx[e.v][0] = e.idx;
		dfs(e.v, u, d + 1);
	}
}

int n, m;
void init() {
	for (int j = 1; j < 20; j++) {
		for (int i = 1; i <= n; i++) {
			if ((1 << j) > dep[i]) continue;
			int to = fa[i][j - 1];
			fa[i][j] = fa[to][j - 1];
			mx[i][j] = max(mx[i][j - 1], mx[to][j - 1]);
			if (mx[i][j] == mx[i][j - 1]) {
				idx[i][j] = idx[i][j - 1];
			} else {
				idx[i][j] = idx[to][j - 1];
			}
		}
	}
}

typedef pair< int, int > pii;
pii query(int x, int y) {
	int res = 0;
	int chose_idx = -1;
	if (dep[x] > dep[y]) swap(x, y);
	for (int j = 19; j >= 0 && dep[x] != dep[y]; j--) {
		if (dep[y] - (1 << j) < dep[x]) continue;
		if (res < mx[y][j]) {
			res = mx[y][j];
			chose_idx = idx[y][j];
		}
		y = fa[y][j];
	}
	if (x == y) return { res, chose_idx };
	for (int j = 19; j >= 0; j--) {
		if (dep[x] - (1 << j) < 0 || fa[x][j] == fa[y][j]) continue;
		if (res < mx[x][j]) {
			res = mx[x][j];
			chose_idx = idx[x][j];
		}
		if (res < mx[y][j]) {
			res = mx[y][j];
			chose_idx = idx[y][j];
		}
		x = fa[x][j],
		y = fa[y][j];
	}

	if (res < mx[x][0]) {
		res = mx[x][0];
		chose_idx = idx[x][0];
	}
	if (res < mx[y][0]) {
		res = mx[y][0];
		chose_idx = idx[y][0];
	}

	return { res, chose_idx };
}

bool vis[maxn];
vector< int > chose_edge;

int main() {
	freopen("data.in", "r", stdin);
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= m; i++) {
		int w;
		scanf("%d", &w);
		edges[i].w = w;
		edges[i].idx = i;
	}
	for (int i = 1; i <= m; i++) {
		int c;
		scanf("%d", &c);
		edges[i].c = c;
	}
	for (int i = 1; i <= m; i++) {
		int u, v;
		scanf("%d %d", &u, &v);
		edges[i].u = u;
		edges[i].v = v;
		f[i] = i;
	}
	int S;
	scanf("%d", &S);

	sort(edges + 1, edges + 1 + m);
	long long res = 0;
	for (int i = 1; i <= m; i++) {
		int u = edges[i].u, v = edges[i].v;
		int fu = find(u), fv = find(v);
		if (fu != fv) {
			f[fv] = fu;
			res += edges[i].w;
			vis[i] = 1;
			chose_edge.push_back(i);
			V[u].push_back((Edge){ u, v, edges[i].w, edges[i].v, i });
			V[v].push_back((Edge){ v, u, edges[i].w, edges[i].v, i });
		}
	}
	long long ans = res;
	int other_chose = -1;
	int pass = -1;

	dfs(1, -1, 0);
	init();

	for (int i = 1; i <= m; i++) {
		int u = edges[i].u, v = edges[i].v;
		auto it = query(u, v);
		long long tmp = res - it.first + edges[i].w;
		tmp -= S / edges[i].c;
		if (ans > tmp) {
			ans = tmp;
			pass = it.second;
			other_chose = i;
		}
	}
	cout << ans << endl;
	// debug(edges[other_chose].w, edges[other_chose].c);
	if (other_chose != -1)
		printf("%d %d\n", edges[other_chose].idx, edges[other_chose].w - S / edges[other_chose].c);

	for (auto idx : chose_edge) {
		if (idx == pass) continue;
		if (idx == other_chose) continue;
		printf("%d %d\n", edges[idx].idx, edges[idx].w);
	}
	return 0;
}