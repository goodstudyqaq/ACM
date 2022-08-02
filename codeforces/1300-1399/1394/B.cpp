/*
n个点m条边，每个点的度不超过k(k<=9),每条边有一个权值，所有边的权值是1~m的全排列.
现在有一个c数组，ci表示，如果一个点的度数为i，那么从这个点会走到连接这个点的权值第ci小的边，
给出所有c的方案，使得从任意一个点走都能回到原处。
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

const int maxn = 2e5 + 5;
const int mod = 1e9 + 7;
typedef pair< long long, long long > pii;

pii operator*(pii a, pii b) {
	return {
		a.first * b.first % mod, a.second * b.second % mod
	};
}

pii operator+(pii a, pii b) {
	return {
		(a.first + b.first) % mod, (a.second + b.second) % mod
	};
}
pii ans_val;

vector< pii > V[maxn];

pii sum[10][10];

long long ans;

int n, m, k;
pii H[maxn];
void dfs(int d, pii now) {
	if (d > k) {
		ans += ans_val == now;
		return;
	}
	for (int i = 1; i <= d; i++) {
		dfs(d + 1, now + sum[d][i]);
	}
}

int main() {
	// freopen("data.in", "r", stdin);
	scanf("%d %d %d", &n, &m, &k);
	int u, v, w;
	for (int i = 1; i <= m; i++) {
		scanf("%d %d %d", &u, &v, &w);
		V[u].push_back({ w, v });
	}

	H[0] = { 1, 1 };
	pii bs = { 233333, 2333333 };
	for (int i = 1; i <= n; i++) {
		H[i] = H[i - 1] * bs;
		ans_val = ans_val + H[i];
	}

	for (int i = 1; i <= n; i++) {
		sort(V[i].begin(), V[i].end());
		int sz = V[i].size();

		for (int j = 0; j < V[i].size(); j++) {
			sum[sz][j + 1] = sum[sz][j + 1] + H[V[i][j].second];
		}
	}

	dfs(1, { 0, 0 });
	cout << ans << endl;
}