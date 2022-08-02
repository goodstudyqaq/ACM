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

const int maxn = 1e5 + 5;
const int mod = 1e9 + 7;
vector< int > V[maxn][2];
int node[maxn];
int ncnt;

void dfs(int u, int pre) {
	debug(u, pre);
	node[u] = ncnt;
	for (auto v : V[u][1]) {
		if (v == pre) continue;
		if (node[v]) continue;
		dfs(v, u);
	}
}

long long quick(long long a, long long b) {
	long long res = 1;
	while (b) {
		if (b % 2) {
			res = res * a % mod;
		}
		b /= 2;
		a = a * a % mod;
	}
	return res;
}

bool dfs2(int u, int flag) {
	node[u] = flag;
	for (auto v : V[u][1]) {
		if (node[v]) {
			if (node[v] != 3 - node[u])
				return false;
		} else {
			bool f = dfs2(v, 3 - flag);
			if (!f) {
				return false;
			}
		}
	}
	return true;
}

int main() {
	freopen("data1.in", "r", stdin);
	int n, m;
	scanf("%d %d", &n, &m);
	int u, v, c;
	for (int i = 1; i <= m; i++) {
		scanf("%d %d %d", &u, &v, &c);
		V[u][c].push_back(v);
		V[v][c].push_back(u);
	}
	for (int i = 1; i <= n; i++) {
		if (!node[i]) {
			++ncnt;
			dfs(i, -1);
		}
	}

	for (int i = 1; i <= n; i++) {
		V[i][1].clear();
	}
	set< pair< int, int > > S;
	for (int i = 1; i <= n; i++) {
		for (auto to : V[i][0]) {
			int u = node[i];
			int v = node[to];
			if (u == v) {
				puts("0");
				return 0;
			}
			if (!S.count({ u, v })) {
				S.insert({ u, v });
				V[u][1].push_back(v);
			}
			// V2[v].push_back(u);
		}
	}

	memset(node, 0, sizeof(node));
	int ncnt2 = 0;
	for (int i = 1; i <= ncnt; i++) {
		if (node[i] == 0) {
			ncnt2++;
			bool f = dfs2(i, 1);
			if (!f) {
				puts("0");
				return 0;
			}
		}
	}
	debug(ncnt2);
	printf("%lld\n", quick(2, ncnt2 - 1));
}