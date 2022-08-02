/*
有两颗树，它们的叶子节点有一条边连向一个共同节点，且这条边在物理上不会相交。。
要求切割掉尽量多的边，并且保证共同节点仍然能到一棵树的根。输出切掉的边的数量
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

const int maxn = 3005;
vector< int > V[3][maxn];
int l[3][maxn], r[3][maxn];

int sz[3][maxn];
int val[3][maxn][maxn];
int dp[maxn];

void dfs(int type, int u, int pre) {
	sz[type][u] = 1;
	for (auto v : V[type][u]) {
		if (v == pre) continue;
		dfs(type, v, u);
		sz[type][u] += sz[type][v];
		l[type][u] = min(l[type][u], l[type][v]);
		r[type][u] = max(r[type][u], r[type][v]);
	}
	val[type][l[type][u]][r[type][u]] = max(val[type][l[type][u]][r[type][u]], sz[type][u]);
}

int main() {
	freopen("data.in", "r", stdin);
	int n;
	scanf("%d", &n);
	for (int type = 1; type <= 2; type++) {

		int num;
		scanf("%d", &num);

		for (int i = 1; i <= num; i++) {
			l[type][i] = n + 10;
		}

		int u;
		for (int i = 1; i <= num - 1; i++) {
			scanf("%d", &u);
			V[type][u].push_back(i + 1);
			V[type][i + 1].push_back(u);
		}
		for (int i = 1; i <= n; i++) {
			scanf("%d", &u);
			l[type][u] = i;
			r[type][u] = i;
		}
		dfs(type, 1, -1);

		val[type][1][n]--;
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j < i; j++) {
			debug(j + 1, i, val[1][j + 1][i], val[2][j + 1][i]);
			dp[i] = max(dp[i], dp[j] + max(val[1][j + 1][i], val[2][j + 1][i]));
		}
		debug(i, dp[i]);
	}
	cout << dp[n] << endl;
}