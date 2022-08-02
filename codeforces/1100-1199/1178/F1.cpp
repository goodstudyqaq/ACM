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

const int mod = 998244353;
vector< int > c;
vector< vector< int > > mi;
vector< vector< long long > > dp;
int n, m;

long long dfs(int l, int r) {
	// debug(l, r);
	if (l >= r) return 1;
	if (dp[l][r] != -1) return dp[l][r];

	int idx = mi[l][r];
	long long tmp1 = 0, tmp2 = 0;

	for (int i = l; i <= idx; i++) {
		tmp1 = (tmp1 + dfs(l, i - 1) * dfs(i, idx - 1) % mod) % mod;
	}
	for (int i = idx; i <= r; i++) {
		tmp2 = (tmp2 + dfs(idx + 1, i) * dfs(i + 1, r) % mod) % mod;
	}
	// debug(l, r, tmp1, tmp2);
	return dp[l][r] = tmp1 * tmp2 % mod;
}

int main() {
#ifdef LOCAL
	freopen("data.in", "r", stdin);
#endif
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n >> m;
	c.resize(n + 1);
	mi.resize(n + 1, vector< int >(n + 1));
	dp.resize(n + 1, vector< long long >(n + 1, -1));
	for (int i = 1; i <= n; i++) {
		cin >> c[i];
	}

	for (int i = 1; i <= n; i++) {
		int val = n + 1;
		mi[i][i] = i;
		for (int j = i; j <= n; j++) {
			if (val > c[j]) {
				mi[i][j] = j;
				val = c[j];
			} else {
				mi[i][j] = mi[i][j - 1];
			}
			// debug(i, j, mi[i][j]);
		}
	}

	cout << dfs(1, n) << endl;
}