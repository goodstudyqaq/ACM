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
vector< int > ans;
vector< int > dp;
vector< int > zero;

void dfs1(int u, int pre) {
	dp[u] = 1;
	for (auto v : V[u]) {
		if (v == pre) continue;
		dfs1(v, u);
		int tmp;
		if (zero[v])
			tmp = 0;
		else
			tmp = dp[v];
		if ((tmp + 1) % mod == 0) {
			zero[u]++;
		} else {
			dp[u] = 1LL * dp[u] * ((tmp + 1) % mod) % mod;
		}
	}
}

void dfs2(int u, int pre) {
	if (zero[u])
		ans[u] = 0;
	else
		ans[u] = dp[u];

	for (auto v : V[u]) {
		if (v == pre) continue;

		// 换根

		int pu = dp[u], pv = dp[v];
		int z1 = zero[u], z2 = zero[v];

		int tmp;
		if (zero[v]) {
			tmp = 0;
		} else {
			tmp = dp[v];
		}

		if ((tmp + 1) % mod == 0) {
			zero[u]--;
		} else {
			dp[u] = 1LL * dp[u] * quick((tmp + 1) % mod, mod - 2) % mod;
		}

		if (zero[u]) {
			tmp = 0;
		} else {
			tmp = dp[u];
		}

		if ((tmp + 1) % mod == 0) {
			zero[v]++;
		} else {
			dp[v] = 1LL * dp[v] * ((tmp + 1) % mod) % mod;
		}
		dfs2(v, u);
		dp[u] = pu;
		dp[v] = pv;
		zero[u] = z1;
		zero[v] = z2;
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
	V.resize(n + 1);
	dp.resize(n + 1);
	ans.resize(n + 1);
	zero.resize(n + 1, 0);
	for (int i = 2; i <= n; i++) {
		int p;
		cin >> p;
		V[p].push_back(i);
		V[i].push_back(p);
	}

	dfs1(1, -1);
	dfs2(1, -1);
	for (int i = 1; i <= n; i++) {
		cout << ans[i] << ' ';
	}
	cout << endl;
	return 0;
}