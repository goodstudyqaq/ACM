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

const int maxn = 1e5 + 5;

struct Edge {
	int u, v, w, idx;
} edges[maxn];
bool cmp(Edge a, Edge b) {
	return a.w < b.w;
}
int f[maxn];
int find(int u) {
	return u == f[u] ? u : f[u] = find(f[u]);
}
int ans[maxn];
vector< pair< int, int > > V[maxn];
int DFN[maxn], LOW[maxn], id;

void tarjan(int u, int pre, int idx) {
	DFN[u] = LOW[u] = ++id;
	for (auto e : V[u]) {
		if (e.first == pre && e.second == idx) continue;
		int v = e.first;
		// debug(u, v);
		if (!DFN[v]) {
			tarjan(v, u, e.second);
			if (DFN[u] < LOW[v]) {
				ans[e.second] = 1;
			}
			LOW[u] = min(LOW[u], LOW[v]);
		} else {
			LOW[u] = min(LOW[u], DFN[v]);
		}
	}
	debug(u, DFN[u], LOW[u]);
}

int main() {
	freopen("data.in", "r", stdin);
	int n, m;
	scanf("%d %d", &n, &m);
	int u, v, w;
	for (int i = 1; i <= m; i++) {
		scanf("%d %d %d", &u, &v, &w);
		edges[i] = (Edge){ u, v, w, i };
	}
	sort(edges + 1, edges + 1 + m, cmp);
	for (int i = 1; i <= n; i++) {
		f[i] = i;
	}

	for (int i = 1; i <= m;) {
		Edge& e = edges[i];
		// debug(e.w);
		int go = i;
		while (go <= m && edges[go].w == e.w) {
			go++;
		}

		for (int j = i; j < go; j++) {
			edges[j].u = find(edges[j].u);
			edges[j].v = find(edges[j].v);

			if (edges[j].u == edges[j].v) {
				ans[edges[j].idx] = 3;
				continue;
			}
			V[edges[j].u].clear();
			V[edges[j].v].clear();
		}

		for (int j = i; j < go; j++) {
			if (edges[j].u == edges[j].v) continue;
			// debug(edges[j].u, edges[j].v);
			V[edges[j].u].push_back({ edges[j].v, edges[j].idx });
			V[edges[j].v].push_back({ edges[j].u, edges[j].idx });
			DFN[edges[j].u] = DFN[edges[j].v] = 0;
		}
		id = 0;
		for (int j = i; j < go; j++) {
			if (DFN[edges[j].u] == 0) {
				tarjan(edges[j].u, -1, -1);
			}
		}

		for (int j = i; j < go; j++) {
			f[find(edges[j].u)] = find(f[edges[j].v]);
		}
		i = go;
	}

	for (int i = 1; i <= m; i++) {
		if (ans[i] == 0) {
			puts("at least one");
		} else if (ans[i] == 1) {
			puts("any");
		} else {
			puts("none");
		}
	}
	return 0;
}