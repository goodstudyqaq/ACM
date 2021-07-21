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

vector< int > color;
vector< vector< int > > V, V2;
vector< int > idx;
int vcnt;

void dfs(int u, int pre, int c) {
	if (color[u] != c) {
		idx[u] = ++vcnt;
	} else {
		idx[u] = idx[pre];
	}
	for (auto v : V[u]) {
		if (v == pre) continue;
		dfs(v, u, color[u]);
	}
}

int node;
int mxd;
void dfs3(int u, int pre, int d) {
	// debug(u, pre, d);
	if (mxd < d) {
		mxd = d;
		node = u;
	}
	for (auto v : V2[u]) {
		if (v == pre) continue;
		dfs3(v, u, d + 1);
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
	color.resize(n + 1);
	V.resize(n + 1);
	idx.resize(n + 1);
	V2.resize(n + 1);
	for (int i = 1; i <= n; i++) {
		cin >> color[i];
	}
	int u, v;
	for (int i = 1; i < n; i++) {
		cin >> u >> v;
		V[u].push_back(v);
		V[v].push_back(u);
	}
	dfs(1, -1, -1);

	if (vcnt == 1) {
		puts("0");
		return 0;
	}

	for (int i = 1; i <= n; i++) {
		int iidx = idx[i];
		// debug(i, iidx);
		for (auto v : V[i]) {
			int vidx = idx[v];
			if (vidx == iidx) continue;
			V2[iidx].push_back(vidx);
		}
	}

	mxd = -1;
	dfs3(1, -1, 0);
	mxd = -1;
	dfs3(node, -1, 0);
	cout << (mxd + 1) / 2 << endl;
	return 0;
}