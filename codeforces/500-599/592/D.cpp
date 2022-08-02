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

const int maxn = 123456 + 10;
vector< int > V[maxn];
bool vis[maxn];
int mxd, chose, chose2;

void dfs(int u, int pre, int d) {
	if (vis[u]) {
		if (mxd < d || (mxd == d && chose > u)) {
			mxd = d;
			chose = u;
		}
	}

	for (auto v : V[u]) {
		if (v == pre) continue;
		dfs(v, u, d + 1);
	}
}

int res;

bool dfs2(int u, int pre, int d) {

	bool f = vis[u];
	if (vis[u]) {
		if (mxd < d || (mxd == d && chose2 > u)) {
			mxd = d;
			chose2 = u;
		}
	}

	for (auto v : V[u]) {
		if (v == pre) continue;
		f |= dfs2(v, u, d + 1);
	}

	if (f && u != chose) {
		res += 2;
	}
	return f;
}

int main() {
	// freopen("data1.in", "r", stdin);
	int n, m;
	scanf("%d %d", &n, &m);
	int u, v;
	for (int i = 1; i <= n - 1; i++) {
		scanf("%d %d", &u, &v);
		V[u].push_back(v);
		V[v].push_back(u);
	}

	for (int i = 1; i <= m; i++) {
		scanf("%d", &u);
		vis[u] = 1;
	}
	dfs(1, -1, 1);

	// printf("%d\n", chose);
	mxd = 0;

	chose2 = chose;
	dfs2(chose, -1, 0);
	debug(res, mxd);
	printf("%d\n", min(chose, chose2));

	printf("%d\n", res - mxd);
}