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

const int maxn = 1005;
const int maxm = 2520;
int k[maxn];
int num[maxn][maxm];
int vis[maxn][maxm];
typedef pair< int, int > pii;
pii _stack[maxn * maxm];
int scnt;
vector< int > V[maxn];

int sum;

int add(int a, int mod) {
	return (a + mod) % mod;
}

void dfs(int u, int w, int flag) {
	if (flag)
		debug(u, w);
	vis[u][w] = 1;
	_stack[scnt++] = { u, w };
	int nxtw = ((w + k[u]) % maxm + maxm) % maxm;
	int sz = V[u].size();
	if (sz == 0) {
		scnt--;
		vis[u][w] = 2;
		return;
	}
	int nxtu = V[u][((w + k[u]) % sz + sz) % sz];
	if (flag)
		debug(nxtu, nxtw, vis[nxtu][nxtw], num[nxtu][nxtw]);
	if (!vis[nxtu][nxtw]) {
		dfs(nxtu, nxtw, flag);
	} else if (vis[nxtu][nxtw] == 1) {
		int now = scnt - 1;
		set< int > S;
		while (now >= 0) {
			S.insert(_stack[now].first);
			if (_stack[now].first == nxtu && _stack[now].second == nxtw) {
				break;
			}
			now--;
		}
		num[u][w] = S.size();
		scnt--;
		vis[u][w] = 2;
		return;
	}
	num[u][w] = num[nxtu][nxtw];
	vis[u][w] = 2;
	scnt--;
}

int main() {
	// freopen("data.in", "r", stdin);
	int n;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &k[i]);
	}
	for (int i = 1; i <= n; i++) {
		int m;
		scanf("%d", &m);
		int u;
		for (int j = 1; j <= m; j++) {
			scanf("%d", &u);
			V[i].push_back(u);
		}
	}

	for (int i = 1; i <= n; i++) {
		for (int j = 0; j < maxm; j++) {
			if (!num[i][j]) {
				sum = 0;
				scnt = 0;
				dfs(i, j, 0);
			}
		}
	}
	// dfs(3, 2519, 1);

	int q;
	scanf("%d", &q);
	while (q--) {
		int x, y;
		scanf("%d %d", &x, &y);
		// debug(x, (y % maxm + maxm) % maxm);
		printf("%d\n", num[x][(y % maxm + maxm) % maxm]);
	}
	return 0;
}