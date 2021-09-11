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

#define next nxt

struct Edge {
	int u, v, next;
	int idx;
	Edge(int _u, int _v, int _nxt, int _idx)
		: u(_u), v(_v), next(_nxt), idx(_idx) {}
	Edge() {}
};
vector< Edge > edges;
vector< int > head;
int tot;
void addedge(int u, int v, int idx) {
	edges[tot] = Edge(u, v, head[u], idx);
	head[u] = tot++;
}

vector< int > DFN, LOW, stk, belong;
int id;
int tot1;
int cnt;
int ans;
int chose_idx;
typedef pair< int, int > pii;
vector< int > res;
vector< bool > vis;
void tarjan(int u, int pre) {
	debug(u, pre);
	DFN[u] = LOW[u] = ++id;
	stk[tot1++] = u;
	for (int i = head[u]; ~i; i = edges[i].nxt) {
		int v = edges[i].v;
		if (v == pre) continue;
		if (!vis[edges[i].idx]) {
			vis[edges[i].idx] = 1;
			res[edges[i].idx] = v;
		}
		if (!DFN[v]) {
			tarjan(v, u);
			LOW[u] = min(LOW[u], LOW[v]);
		} else {
			LOW[u] = min(LOW[u], DFN[v]);
		}
	}

	if (LOW[u] == DFN[u]) {
		cnt++;
		int v;
		int num = 0;
		do {
			v = stk[tot1 - 1];
			belong[v] = cnt;
			tot1--;
			num++;
		} while (v != u);

		if (num > ans) {
			ans = num;
			chose_idx = cnt;
		}
	}
}
vector< pii > e;

vector< vector< pii > > V2;

void dfs(int u, int pre) {
	for (auto it : V2[u]) {
		if (it.first == pre) continue;

		auto edg = e[it.second];
		int real_u = edg.first;
		int real_v = edg.second;
		if (belong[real_u] == u) {
			res[it.second] = real_u;
		} else {
			res[it.second] = real_v;
		}
		dfs(it.first, u);
	}
}

int main() {
#ifdef LOCAL
	freopen("data.in", "r", stdin);
#endif
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n, m;
	cin >> n >> m;
	edges.resize(m * 2);
	head.resize(n + 1, -1);
	DFN.resize(n + 1);
	LOW.resize(n + 1);
	stk.resize(n + 1);
	belong.resize(n + 1);
	res.resize(m + 1);
	e.resize(m + 1);
	vis.resize(m + 1);
	for (int i = 1; i <= m; i++) {
		int u, v;
		cin >> u >> v;
		e[i] = { u, v };
		addedge(u, v, i);
		addedge(v, u, i);
	}
	tarjan(1, 0);
	// 缩点

	// for (int i = 1; i <= n; i++) {
	// 	debug(i, belong[i]);
	// }

	V2.resize(cnt + 1);
	cout << ans << '\n';

	for (int i = 1; i <= m; i++) {
		auto it = e[i];
		int u = it.first, v = it.second;
		if (belong[u] != belong[v]) {
			u = belong[u], v = belong[v];
			V2[u].push_back({ v, i });
			V2[v].push_back({ u, i });
		}
	}
	dfs(chose_idx, -1);

	for (int i = 1; i <= m; i++) {
		int tmp = res[i];
		auto it = e[i];
		if (it.first != tmp) {
			cout << it.first << ' ' << tmp << '\n';
		} else {
			cout << it.second << ' ' << tmp << '\n';
		}
	}
	return 0;
}