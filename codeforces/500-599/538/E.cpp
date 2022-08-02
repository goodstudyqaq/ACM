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

vector< vector< int > > V;
vector< int > dp, dp2;
vector< int > sz;

void dfs(int u) {
	if (V[u].size() == 0) {
		sz[u] = 1;
	}
	for (auto v : V[u]) {
		dfs(v);
		sz[u] += sz[v];
	}
}
typedef pair< int, int > pii;
int dfs2(int u, int d) {

	if (V[u].size() == 0) {
		return 1;
	}

	if (d % 2) {
		int res = sz[1];
		for (auto v : V[u]) {
			res = min(res, dfs2(v, d + 1));
		}
		return res;
	} else {
		int res = 0;
		for (auto v : V[u]) {
			res += dfs2(v, d + 1);
		}
		return res;
	}
}

int main() {
#ifdef LOCAL
	freopen("data.in", "r", stdin);
#endif
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n;
	cin >> n;
	int u, v;
	V.resize(n + 1);
	for (int i = 1; i < n; i++) {
		cin >> u >> v;
		V[u].push_back(v);
	}
	dp.resize(n + 1);
	dp2.resize(n + 1);
	sz.resize(n + 1, 0);
	dfs(1);

	int val1 = dfs2(1, 1);
	int val2 = dfs2(1, 0);
	cout << sz[1] - val1 + 1 << ' ' << val2 << endl;

	return 0;
}