/*
求四元环，图论做法
https://blog.csdn.net/weixin_43466755/article/details/112985722
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

const int maxn = 1e5 + 5;
vector< int > V[maxn];
int ax[2 * maxn], acnt;
vector< int > g[maxn * 3], g2[maxn * 3];
int rk[maxn * 3];
int cnt[maxn * 3];
vector< int > ans;
int deg[maxn * 3];
int f[maxn * 3];

int n;
bool cmp(int a, int b) {
	if (deg[a] != deg[b]) {
		return deg[a] < deg[b];
	}
	return a < b;
}
void init() {
	for (int i = 1; i <= n; i++) {
		V[i].clear();
	}
	acnt = 0;
	ans.clear();
}

void init2() {
	for (int i = 1; i <= n + acnt; i++) {
		g[i].clear();
		g2[i].clear();
		cnt[i] = 0;
		deg[i] = 0;
	}
}

bool check() {

	for (int u = 1; u <= n + acnt; u++) {
		for (auto v : g[u]) {
			for (auto w : g2[v]) {
				if (rk[w] > rk[u]) {
					if (cnt[w]) {
						ans.push_back(u);
						ans.push_back(v);
						ans.push_back(w);
						ans.push_back(cnt[w]);
						sort(ans.begin(), ans.end());
						return true;
					}
					cnt[w] = v;
				}
			}
		}
		for (auto v : g[u]) {
			for (auto w : g2[v]) {
				if (rk[w] > rk[u]) {
					cnt[w] = 0;
				}
			}
		}
	}
	return false;
}

int main() {
	freopen("data.in", "r", stdin);
	int T;
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		init();
		for (int i = 1; i <= n; i++) {
			int k, a;
			scanf("%d", &k);
			for (int j = 1; j <= k; j++) {
				scanf("%d", &a);
				V[i].push_back(a);
				ax[++acnt] = a;
			}
		}

		sort(ax + 1, ax + 1 + acnt);
		acnt = unique(ax + 1, ax + 1 + acnt) - ax - 1;
		init2();
		debug(acnt);

		for (int i = 1; i <= n; i++) {
			for (int j = 0; j < V[i].size(); j++) {
				int idx = lower_bound(ax + 1, ax + 1 + acnt, V[i][j]) - ax;
				idx = idx + n;
				g[i].push_back(idx);
				g[idx].push_back(i);
				deg[i]++;
				deg[idx]++;
			}
		}

		for (int i = 1; i <= n + acnt; i++) {
			f[i] = i;
		}
		sort(f + 1, f + 1 + n + acnt, cmp);
		for (int i = 1; i <= n + acnt; i++) {
			rk[f[i]] = i;
		}
		for (int u = 1; u <= n + acnt; u++) {
			for (auto v : g[u]) {
				if (deg[u] < deg[v] || (deg[u] == deg[v] && u < v)) {
					g2[u].push_back(v);
				}
			}
		}
		if (check()) {
			printf("%d %d\n", ans[0], ans[1]);
		} else {
			puts("-1");
		}
	}
}