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
vector< int > DFN, LOW, stk;
int scnt;
vector< int > belong;
int cnt;
int id;

void tarjan(int u, int pre) {
	DFN[u] = LOW[u] = ++id;
	stk[scnt++] = u;

	for (auto it : V[u]) {
		if (it.first == pre) continue;
		int v = it.first;
		if (!DFN[it.first]) {
			tarjan(it.first, u);
			LOW[u] = min(LOW[u], LOW[v]);
		} else {
			LOW[u] = min(LOW[u], DFN[v]);
		}
	}

	if (LOW[u] == DFN[u]) {
		cnt++;
		int v;
		do {
			v = stk[scnt - 1];
			belong[v] = cnt;
			scnt--;
		} while (v != u);
	}
}

typedef pair< pii, int > piii;
vector< piii > edges;
vector< int > color;

int a, b;
void dfs(int u, int pre, bool f) {
	debug(u, pre, f);
	f |= color[u];
	if (u == belong[b]) {
		if (f) {
			cout << "YES" << '\n';
		} else {
			cout << "NO" << '\n';
		}
		exit(0);
	}

	// 有重边 先去重
	map< int, bool > M;
	for (auto it : V[u]) {
		if (it.first == pre) continue;
		M[it.first] |= it.second;
	}

	for (auto it : M) {
		dfs(it.first, u, f | it.second);
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
	V.resize(n + 1);
	DFN.resize(n + 1);
	LOW.resize(n + 1);
	color.resize(n + 1);
	belong.resize(n + 1);
	stk.resize(n + 1);
	for (int i = 1; i <= m; i++) {
		int x, y, z;
		cin >> x >> y >> z;
		V[x].push_back({ y, z });
		V[y].push_back({ x, z });
		edges.push_back({ { x, y }, z });
	}

	cin >> a >> b;
	tarjan(1, 0);
	for (int i = 1; i <= n; i++) {
		V[i].clear();
	}

	for (int i = 1; i <= n; i++) {
		debug(i, belong[i]);
	}

	for (int i = 0; i < m; i++) {
		auto it = edges[i];
		int u = it.first.first, v = it.first.second;
		bool f = it.second;
		if (belong[u] != belong[v]) {
			V[belong[u]].push_back({ belong[v], f });
			V[belong[v]].push_back({ belong[u], f });
		} else {
			color[belong[u]] = color[belong[u]] | f;
		}
	}

	dfs(belong[a], 0, 0);
	return 0;
}