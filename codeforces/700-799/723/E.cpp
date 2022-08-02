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

const int maxn = 205;
vector< int > V[maxn];
int n, m;

bool vis[maxn][maxn];

vector< pair< int, int > > ans;
void dfs(int u) {
	for (auto v : V[u]) {
		if (!vis[u][v] && !vis[v][u]) {
			vis[u][v] = vis[v][u] = 1;
			if (u && v) {
				ans.push_back({ u, v });
			}
			dfs(v);
		}
	}
}

void init() {
	for (int i = 0; i <= n; i++) {
		V[i].clear();
		for (int j = 0; j <= n; j++) {
			vis[i][j] = 0;
		}
	}
	ans.clear();
}

int main() {
	freopen("data.in", "r", stdin);
	int T;
	scanf("%d", &T);
	while (T--) {
		scanf("%d %d", &n, &m);
		init();

		int u, v;
		for (int i = 1; i <= m; i++) {
			scanf("%d %d", &u, &v);
			V[u].push_back(v);
			V[v].push_back(u);
		}
		int cnt = 0;
		for (int i = 1; i <= n; i++) {
			if (V[i].size() % 2) {
				V[0].push_back(i);
				V[i].push_back(0);
				cnt++;
			}
		}

		for (int i = 1; i <= n; i++) {
			dfs(i);
		}
		printf("%d\n", n - cnt);
		for (auto e : ans) {
			printf("%d %d\n", e.first, e.second);
		}
	}
	return 0;
}