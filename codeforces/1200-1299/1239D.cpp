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

const int maxn = 2e6 + 5;
const int maxm = 1e6 + 5;
struct Edge {

	int u, v, next;
	Edge(int _u, int _v, int _nxt)
		: u(_u), v(_v), next(_nxt) {}
	Edge() {}
} edges[maxm];
int head[maxn], tot;
void addedge(int u, int v) {
	edges[tot] = Edge(u, v, head[u]);
	head[u] = tot++;
}

int DFN[maxn], LOW[maxn], vis[maxn], id;
int belong[maxn], cnt;
int _stack[maxn], tot1;

void tarjan(int u) {
	DFN[u] = LOW[u] = ++id;
	_stack[tot1++] = u;
	vis[u] = 1;
	for (int i = head[u]; ~i; i = edges[i].next) {
		int v = edges[i].v;
		if (!DFN[v]) {
			tarjan(v);
			LOW[u] = min(LOW[u], LOW[v]);
		} else if (vis[v])
			LOW[u] = min(LOW[u], DFN[v]);
	}
	if (LOW[u] == DFN[u]) {
		cnt++;
		int v;
		do {
			v = _stack[tot1 - 1];
			vis[v] = 0;
			belong[v] = cnt;
			tot1--;
		} while (v != u);
	}
}
void solve(int N) {
	for (int i = 1; i <= 2 * N; i++) DFN[i] = 0;
	cnt = 0;
	for (int i = 1; i <= N; i++)
		if (!DFN[i]) {
			id = 0;
			tarjan(i);
		}
}

int main() {
	// freopen("data.in", "r", stdin);
	int T;
	scanf("%d", &T);
	while (T--) {
		int n, m;
		scanf("%d %d", &n, &m);

		for (int i = 1; i <= 2 * n; i++) {
			head[i] = -1;
		}
		tot = 0;
		int u, v;
		for (int i = 1; i <= m; i++) {
			scanf("%d %d", &u, &v);
			if (u != v) {
				addedge(u, v + n);
			}
		}
		for (int i = 1; i <= n; i++) {
			addedge(i + n, i);
		}

		solve(n);
		if (cnt == 1) {
			puts("No");
			continue;
		}

		puts("Yes");
		vector< int > ans1, ans2;
		for (int i = 1; i <= n; i++) {
			if (belong[i] == 1) {
				ans1.push_back(i);
			} else {
				ans2.push_back(i);
			}
		}

		printf("%d %d\n", ans1.size(), ans2.size());
		for (auto u : ans1) {
			printf("%d ", u);
		}
		puts("");
		for (auto u : ans2) {
			printf("%d ", u);
		}
		puts("");
	}
	return 0;
}