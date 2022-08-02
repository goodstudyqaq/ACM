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
int w[maxn];
vector< int > V[maxn];

int DFN[maxn], LOW[maxn], fa[maxn], id;
void dfs(int u, int pre) {

	DFN[u] = LOW[u] = ++id;
	fa[u] = pre;
	for (auto v : V[u]) {
		if (v == pre) continue;
		if (!DFN[v]) {
			dfs(v, u);
			LOW[u] = min(LOW[u], LOW[v]);
		} else {
			LOW[u] = min(LOW[u], DFN[v]);
		}
	}
}
int f[maxn];
int find(int u) {
	return f[u] == u ? u : f[u] = find(f[u]);
}
long long cnt[maxn];
int cnt2[maxn];

struct Edge {
	int u, v, nxt;
	Edge(int _u, int _v, int _nxt)
		: u(_u), v(_v), nxt(_nxt) {}
	Edge() {}
} edges[maxn * 2];
int head[maxn], tot;
void add_edge(int u, int v) {
	edges[tot] = Edge(u, v, head[u]);
	head[u] = tot++;
}

int n, m;
bool flag[maxn];
long long dp[maxn][2];
bool vis[maxn];
void dfs2(int u, int pre) {
	// debug(u, pre, cnt[u], cnt2[u]);
	long long res = cnt[u];
	long long mx = 0;
	bool f = (cnt2[u] > 1);
	vis[u] = 1;
	for (int i = head[u]; ~i; i = edges[i].nxt) {
		Edge& e = edges[i];
		if (e.v == pre) continue;
		debug(e.v);
		assert(vis[e.v] == 0);
		dfs2(e.v, u);
		f |= flag[e.v];
		if (flag[e.v]) {
			res += dp[e.v][1];
		}
	}
	flag[u] = f;
	if (!flag[u])
		dp[u][1] = 0;
	else
		dp[u][1] = res;
	for (int i = head[u]; ~i; i = edges[i].nxt) {
		Edge& e = edges[i];
		if (flag[e.v]) {
			dp[u][0] = max(dp[u][0], res - dp[e.v][1] + dp[e.v][0]);
		} else {
			dp[u][0] = max(dp[u][0], dp[e.v][0] + res);
		}
	}
	dp[u][0] = max(dp[u][0], res);
}

void Main() {
	// freopen("data.in", "r", stdin);
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &w[i]);
	}

	int u, v;
	for (int i = 1; i <= m; i++) {
		scanf("%d %d", &u, &v);
		V[u].push_back(v);
		V[v].push_back(u);
	}
	dfs(1, 0);
	for (int i = 1; i <= n; i++) f[i] = i, cnt[i] = w[i], cnt2[i] = 1;
	for (int i = 2; i <= n; i++) {
		int u = fa[i], v = i;
		if (DFN[u] < LOW[v]) continue;
		int fu = find(u), fv = find(v);
		f[fv] = fu;
		cnt[fu] += cnt[fv];
		cnt2[fu] += cnt2[fv];
	}

	for (int i = 1; i <= n; i++) {
		debug(i, f[i], cnt[f[i]]);
	}

	memset(head, -1, sizeof(head));
	set< pair< int, int > > S;
	for (int i = 1; i <= n; i++) {
		int fu = find(i);
		for (auto v : V[i]) {
			int fv = find(v);
			if (fu != fv) {
				if (S.count({ min(fu, fv), max(fu, fv) })) continue;
				S.insert({ min(fu, fv), max(fu, fv) });
				add_edge(fu, fv);
				add_edge(fv, fu);
			}
		}
		V[i].clear();
	}

	int s;
	scanf("%d", &s);
	int fs = find(s);
	dfs2(fs, -1);
	cout << max(dp[fs][0], dp[fs][1]) << endl;
}

int main() {
#ifdef OPENSTACK
	int size = 70 << 20;  // 256MB
	char* p = ( char* )malloc(size) + size;
#if (defined _WIN64) or (defined __unix)
	__asm__("movq %0, %%rsp\n" ::"r"(p));
#else
	__asm__("movl %0, %%esp\n" ::"r"(p));
#endif
#endif
	Main();
#ifdef OPENSTACK
	exit(0);
#else
	return 0;
#endif
}