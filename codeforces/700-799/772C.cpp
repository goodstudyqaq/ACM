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

vector< int > vis;
vector< vector< int > > V2;
vector< int > dp;

vector< vector< int > > V;
vector< int > go;
int dfs(int u) {
	if (dp[u] != -1) return dp[u];
	int res = V[u].size();
	for (auto it : V2[u]) {
		int tmp = dfs(it) + V[u].size();
		if (res < tmp) {
			res = tmp;
			go[u] = it;
		}
	}
	debug(u, res);
	return dp[u] = res;
}

long long extgcd(long long a, long long b, long long& x, long long& y) {
	if (a == 0 && b == 0) return -1;
	if (b == 0) {
		x = 1;
		y = 0;
		return a;
	}
	long long d = extgcd(b, a % b, y, x);
	y -= a / b * x;
	return d;
}

int main() {
#ifdef LOCAL
	freopen("data.in", "r", stdin);
#endif
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n, m;
	cin >> n >> m;
	vis.resize(m, 0);
	go.resize(m, -1);
	dp.resize(m, -1);
	for (int i = 1; i <= n; i++) {
		int val;
		cin >> val;
		vis[val] = 1;
	}
	V.resize(m);

	for (int i = 1; i < m; i++) {
		if (vis[i]) continue;
		int val = __gcd(i, m);
		V[val].push_back(i);
	}
	V2.resize(m);
	vector< int > in(m, 0);

	for (int i = 1; i < m; i++) {
		if (V[i].size() == 0) continue;
		for (int j = i * 2; j < m; j += i) {
			if (V[j].size() == 0) continue;
			V2[i].push_back(j);
			in[j]++;
		}
	}

	int ans = -1;
	int chose_begin = -1;

	for (int i = 1; i < m; i++) {
		if (in[i] == 0) {
			int tmp = dfs(i);
			if (ans < tmp) {
				ans = tmp;
				chose_begin = i;
			}
		}
	}
	debug(ans);

	vector< int > res;
	int now = chose_begin;
	while (now != -1) {
		for (int i = 0; i < V[now].size(); i++) {
			res.push_back(V[now][i]);
		}
		now = go[now];
	}

	if (!vis[0]) res.push_back(0);

	if (res.size() == 0) {
		cout << 0 << endl;
		return 0;
	}
	cout << res.size() << endl;

	vector< int > real_ans;
	real_ans.push_back(res[0]);

	for (int i = 1; i < res.size(); i++) {

		if (res[i] == 0) {
			real_ans.push_back(0);
			continue;
		}

		long long x, y;
		int _d = extgcd(res[i - 1], m, x, y);

		int dx = m / _d;

		while (x < 0) x += dx;
		x = x * (res[i] / _d) % m;
		real_ans.push_back(x);
	}

	for (int i = 0; i < real_ans.size(); i++) {
		cout << real_ans[i] << ' ';
	}
	cout << endl;
	return 0;
}