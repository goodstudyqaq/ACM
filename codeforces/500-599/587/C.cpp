#pragma GCC optimize(3, "Ofast", "inline")

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

const int K = 10;

const int maxn = 1e5 + 5;
struct pset {
	const static int tr = 10;
	int S[K];
	int sz = 0;

	void insert(int v) {
		auto it = lower_bound(S, S + sz, v);
		if (it != S + sz && *it == v) return;
		if (sz == tr && v < S[sz - 1]) sz--;
		if (sz < tr) S[sz++] = v;
		for (int i = sz - 1; i >= 1; i--)
			if (S[i] < S[i - 1]) swap(S[i], S[i - 1]);
	}

	void merge(pset& ps) {
		int a[maxn], asz = 0;
		int cur = 0;
		for (int i = 0; i < sz && asz < K; i++) {
			while (cur < ps.sz && ps.S[cur] <= S[i] && asz < K) a[asz++] = ps.S[cur++];
			if (asz < K) a[asz++] = S[i];
		}
		while (cur < ps.sz && asz < K) a[asz++] = ps.S[cur++];
		for (int i = 0; i < asz; i++) S[i] = a[i];
		sz = asz;
	}
};

vector< int > V[maxn];

int dp[maxn][30];
pset small[maxn][30];
int dep[maxn];

void dfs(int u, int pre, int d) {
	dep[u] = d;
	dp[u][0] = pre;
	for (auto v : V[u]) {
		if (v == pre) continue;
		dfs(v, u, d + 1);
	}
}

void rmq(int n) {
	for (int i = 1; i < 20; i++) {
		for (int j = 1; j <= n; j++) {
			if ((1 << i) > dep[j]) continue;
			int k = dp[j][i - 1];
			dp[j][i] = dp[k][i - 1];
			small[j][i] = small[j][i - 1];
			small[j][i].merge(small[k][i - 1]);
		}
	}
}

pair< int, pset > query(int x, int y, int a) {

	pset res;
	if (dep[x] > dep[y]) swap(x, y);
	for (int j = 19; j >= 0 && dep[x] != dep[y]; j--) {
		if (dep[y] - (1 << j) < dep[x]) continue;
		res.merge(small[y][j]);

		y = dp[y][j];
	}

	if (x == y) {
		res.merge(small[y][0]);
		return { x, res };
	}
	for (int j = 19; j >= 0; j--) {
		if (dep[x] - (1 << j) < 0 || dp[x][j] == dp[y][j]) continue;
		res.merge(small[x][j]);
		res.merge(small[y][j]);
		x = dp[x][j];
		y = dp[y][j];
	}
	res.merge(small[x][1]);
	res.merge(small[y][0]);
	return { dp[x][0], res };
}

int main() {
	// freopen("data1.in", "r", stdin);
	int n, m, q;
	scanf("%d %d %d", &n, &m, &q);
	int u, v;
	for (int i = 1; i <= n - 1; i++) {
		scanf("%d %d", &u, &v);
		V[u].push_back(v);
		V[v].push_back(u);
	}
	for (int i = 1; i <= m; i++) {
		scanf("%d", &u);
		small[u][0].insert(i);
	}

	dfs(1, -1, 1);
	rmq(n);

	int a;
	while (q--) {
		scanf("%d %d %d", &u, &v, &a);
		pair< int, pset > res = query(u, v, a);

		int mi = min(int(res.second.sz), a);
		printf("%d", mi);
		int now = 0;
		for (int i = 0; i < mi; i++) {
			printf(" %d", res.second.S[i]);
		}
		puts("");
	}
	return 0;
}