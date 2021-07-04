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
const int maxn = 1e5 + 5;
int p[maxn];

vector< int > V[maxn];
int color[maxn];
long long dp[maxn][2];

void dfs(int u, int pre) {
	dp[u][color[u]] = 1;
	for (auto v : V[u]) {
		if (v == pre) continue;
		dfs(v, u);
		long long tmp0 = dp[u][0], tmp1 = dp[u][1];
		dp[u][0] = 1LL * tmp0 * ((dp[v][0] + dp[v][1]) % mod) % mod;
		dp[u][1] = ((tmp0 * dp[v][1] % mod + tmp1 * dp[v][0] % mod) % mod + tmp1 * dp[v][1] % mod) % mod;
	}
}

int main() {
	// freopen("data.in", "r", stdin);
	int n;
	scanf("%d", &n);
	int u;
	for (int i = 1; i < n; i++) {
		scanf("%d", &u);
		V[i].push_back(u);
		V[u].push_back(i);
	}
	for (int i = 0; i < n; i++) {
		scanf("%d", &color[i]);
	}
	dfs(0, -1);
	// for (int i = 0; i < n; i++) {
	// 	debug(i, dp[i][0], dp[i][1]);
	// }
	cout << dp[0][1] << endl;
}