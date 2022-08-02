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

const int maxn = 1e6 + 5;
typedef pair< int, int > pii;
pii edges[maxn];
int ecnt;
set< pii > G[maxn];
int in[maxn];
bool vis[maxn];
deque< pii > path;

void dfs(int u) {
	vis[u] = 1;
	if (G[u].size() == 0) return;
	while (G[u].size()) {
		auto it = *G[u].begin();
		G[u].erase(G[u].begin());
		G[it.first].erase({ u, it.second });
		path.push_back(edges[it.second]);
		dfs(it.first);
	}
}

int n, m;

vector< pii > path2;

vector< pii > res;

void cal() {
	int sz = path2.size();
	for (int i = 0; i < sz; i++) {
		if (i % 2 == 0 || i == sz - 1) {
			res.push_back(path2[i]);
		}
	}
	path2.clear();
}

void work() {

	debug(path.size());
	// for (auto it : path) {
	// 	debug(it);
	// }

	bool have = false;
	for (auto it : path) {
		if (it.first == 0 || it.second == 0) {
			have = true;
			break;
		}
	}

	if (have) {
		while (path.front().first != 0 && path.front().second != 0) {
			auto it = path.front();
			path.pop_front();
			path.push_back(it);
		}
	}

	while (!path.empty()) {
		auto it = path.front();
		if (path.front().first == 0 || path.front().second == 0) {
			cal();
		} else {
			path2.push_back(it);
		}
		path.pop_front();
	}
	cal();
}
int in2[maxn];
int main() {
	// 	freopen("data.in", "r", stdin);
	scanf("%d %d", &n, &m);
	int u, v;
	for (int i = 1; i <= m; i++) {
		scanf("%d %d", &u, &v);
		edges[++ecnt] = { u, v };
		G[u].insert({ v, ecnt });
		G[v].insert({ u, ecnt });
		in[u]++;
		in[v]++;
	}

	for (int i = 1; i <= n; i++) {
		if (in[i] % 2) {
			debug(i);
			edges[++ecnt] = { i, 0 };
			G[i].insert({ 0, ecnt });
			G[0].insert({ i, ecnt });
		}
	}

	for (int i = 1; i <= n; i++) {
		if (vis[i]) continue;
		dfs(i);
		work();
	}

	cout << res.size() << endl;
	for (auto it : res) {
		printf("%d %d\n", it.first, it.second);
		in2[it.first]++;
		in2[it.second]++;
	}

	// for (int i = 1; i <= n; i++) {
	// 	debug(i, in[i], in2[i]);
	// }

	return 0;
}