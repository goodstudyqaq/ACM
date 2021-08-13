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
vector< vector< int > > dp;

void dfs(int u, int pre) {
	for (auto v : V[u]) {
		if (v == pre) continue;
		dfs(v, u);
		int t1 = max(dp[v][0], dp[v][1]);
		int t2 = max(t1, dp[v][2]);
		dp[u][2] = max(t2 + dp[u][2], dp[u][1] + t1 + 1);
		dp[u][1] = max(t2 + dp[u][1], dp[u][0] + t1 + 1);
		dp[u][0] += t2;
	}
}

int main() {
#ifdef LOCAL
	freopen("data.in", "r", stdin);
#endif
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n, x, y;
	cin >> n >> x >> y;
	V.resize(n + 1);
	for (int i = 1; i < n; i++) {
		int u, v;
		cin >> u >> v;
		V[u].push_back(v);
		V[v].push_back(u);
	}

	long long ans;
	if (x == y) {
		ans = 1LL * x * (n - 1);
	} else if (x < y) {
		dp.resize(n + 1, vector< int >(3, 0));
		dfs(1, -1);
		int val = max({ dp[1][0], dp[1][1], dp[1][2] });
		ans = 1LL * val * x + 1LL * (n - 1 - val) * y;
	} else {
		bool flag = false;
		for (int i = 1; i <= n; i++) {
			if (V[i].size() == n - 1) {
				flag = true;
				break;
			}
		}
		if (flag) {
			ans = 1LL * (n - 2) * y + x;
		} else {
			ans = 1LL * (n - 1) * y;
		}
	}
	cout << ans << endl;
	return 0;
}