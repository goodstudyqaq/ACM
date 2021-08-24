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
const int mod = 1e9 + 7;
int quick(int a, int b) {
	int res = 1;
	while (b) {
		if (b % 2) res = 1LL * res * a % mod;
		b /= 2;
		a = 1LL * a * a % mod;
	}
	return res;
}

const int inv2 = quick(2, mod - 2);

vector< vector< int > > V;
vector< vector< int > > f;
int n;
void init() {
	f.resize(n + 1, vector< int >(n + 1, 0));

	for (int i = 1; i <= n; i++) {
		f[0][i] = 1;
	}

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			f[i][j] = 1LL * (f[i - 1][j] + f[i][j - 1]) % mod * inv2 % mod;
		}
	}
}

vector< int > fa, dep;
void dfs(int u, int pre, int d) {
	dep[u] = d;
	fa[u] = pre;
	for (auto it : V[u]) {
		if (it == pre) continue;
		dfs(it, u, d + 1);
	}
}

int get_f(int u, int v) {
	if (dep[u] < dep[v]) swap(u, v);
	while (dep[u] > dep[v]) u = fa[u];
	if (u == v) return u;
	while (u != v) {
		u = fa[u];
		v = fa[v];
	}
	return u;
}

int cal() {
	int ans = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j < i; j++) {
			int father = get_f(i, j);
			ans = (ans + f[dep[i] - dep[father]][dep[j] - dep[father]]) % mod;
		}
	}
	return ans;
}

int main() {
#ifdef LOCAL
	freopen("data.in", "r", stdin);
#endif
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n;
	init();
	int u, v;
	V.resize(n + 1);
	fa.resize(n + 1);
	dep.resize(n + 1);
	for (int i = 1; i < n; i++) {
		cin >> u >> v;
		V[u].push_back(v);
		V[v].push_back(u);
	}

	int ans = 0;
	for (int i = 1; i <= n; i++) {
		dfs(i, -1, 0);
		int tmp = cal();
		ans = (ans + tmp) % mod;
	}
	ans = 1LL * ans * quick(n, mod - 2) % mod;
	cout << ans << endl;
	return 0;
}