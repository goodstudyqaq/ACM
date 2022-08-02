/*
给定一个图，以及q个tuple(u,v,w),对于一个tuple来说，从u到v经过的edge的边权和小于等于w，那么经过的边是有用的，问有用的边的个数
*/

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

const int maxn = 607;
const long long inf = 0x3f3f3f3f3f3f;
long long g[maxn][maxn];
long long d[maxn][maxn];
typedef array< int, 3 > arr;
arr edge[maxn * maxn];
bool ok[maxn][maxn];

vector< pair< int, int > > V[maxn];
int main() {
	// 	freopen("data1.in", "r", stdin);
	int n, m;
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			g[i][j] = inf;
			d[i][j] = inf;
		}
		g[i][i] = 0;
	}
	// memset(g, inf, sizeof(g));
	int u, v, w;
	for (int i = 1; i <= m; i++) {
		scanf("%d %d %d", &u, &v, &w);
		d[u][v] = d[v][u] = w;
		g[u][v] = g[v][u] = w;
		edge[i][0] = u;
		edge[i][1] = v;
		edge[i][2] = w;
	}
	for (int k = 1; k <= n; k++) {
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				if (g[i][j] > g[i][k] + g[k][j]) {
					g[i][j] = g[i][k] + g[k][j];
				}
			}
		}
	}

	int q;
	scanf("%d", &q);
	for (int i = 1; i <= q; i++) {
		scanf("%d %d %d", &u, &v, &w);
		V[u].push_back({ v, w });
	}
	for (int a = 1; a <= n; a++) {
		if (V[a].size()) {
			for (int y = 1; y <= n; y++) {
				// find smallest b
				long long res = 1e18;
				for (auto p : V[a]) {
					res = min(res, g[y][p.first] - p.second);
				}
				debug(y, res);
				for (int x = 1; x <= n; x++)
					if (d[x][y] != inf) {
						long long tmp = g[a][x] + d[x][y];
						if (tmp + res <= 0) {
							ok[x][y] = ok[y][x] = 1;
						}
					}
			}
		}
	}
	int ans = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = i + 1; j <= n; j++)
			if (ok[i][j]) {
				debug(i, j);
				ans++;
			}
	}
	cout << ans << endl;
}