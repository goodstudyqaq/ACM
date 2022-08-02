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
const int mod2 = 1e9 + 9;
const int maxn = 1 << 17;
typedef pair< int, int > pii;

vector< pii > V[maxn];

int vis[maxn];
pii _stack[maxn];
int scnt;

long long cnt[50][maxn], ccnt;
long long cnt2[50][maxn], ccnt2;

void dfs(int u, int pre) {
	vis[u] = 1;
	for (auto v : V[u]) {
		int to = v.first;
		int w = v.second;
		if (to == pre) continue;
		if (!vis[to]) {
			_stack[++scnt] = { u, w };
			dfs(to, u);
			--scnt;
		} else if (vis[to] == 1) {
			int now = scnt;
			++ccnt;
			cnt[ccnt][w]++;
			++ccnt2;
			cnt2[ccnt2][w]++;
			while (true) {
				auto tmp = _stack[now];
				cnt[ccnt][tmp.second]++;
				cnt2[ccnt2][tmp.second]++;
				if (tmp.first == to) {
					break;
				}
				now--;
			}
		}
	}
	vis[u] = 2;
}

long long quick(long long a, long long b, long long mod) {
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
const int inv2 = (mod + 1) / 2;

void FWT(long long a[], int n, int flag, int mod) {
	for (int d = 1; d < n; d <<= 1)
		for (int i = 0; i < n; i += (d << 1))
			for (int j = 0; j < d; j++) {
				int x = a[i + j], y = a[i + j + d];
				a[i + j] = (x + y) % mod;
				a[i + j + d] = (x - y) % mod;
				if (flag == -1) {
					a[i + j] = 1LL * a[i + j] * inv2 % mod;
					a[i + j + d] = 1LL * a[i + j + d] * inv2 % mod;
				}
			}
}

void FWT_xor(long long* a, int opt, int MOD) {
	for (int i = 1; i < maxn; i <<= 1)
		for (int p = i << 1, j = 0; j < maxn; j += p)
			for (int k = 0; k < i; ++k) {
				int X = a[j + k], Y = a[i + j + k];
				a[j + k] = (X + Y) % MOD;
				a[i + j + k] = (X + MOD - Y) % MOD;
				if (opt == -1) a[j + k] = 1ll * a[j + k] * inv2 % MOD, a[i + j + k] = 1ll * a[i + j + k] * inv2 % MOD;
			}
}

int main() {
	// freopen("data.in", "r", stdin);
	int n, m;
	scanf("%d %d", &n, &m);
	int u, v, w;
	int ans = 0;
	for (int i = 1; i <= m; i++) {
		scanf("%d %d %d", &u, &v, &w);
		V[u].push_back({ v, w });
		V[v].push_back({ u, w });
		ans ^= w;
	}

	for (int i = 1; i <= n; i++) {
		if (!vis[i]) {
			dfs(i, -1);
		}
	}

	cnt[0][ans] = 1;
	cnt2[0][ans] = 1;
	FWT_xor(cnt[0], 1, mod);
	FWT_xor(cnt2[0], 1, mod2);
	for (int i = 1; i <= ccnt2; i++) {
		FWT_xor(cnt[i], 1, mod);
		FWT_xor(cnt2[i], 1, mod2);
		for (int j = 0; j < maxn; j++) {
			cnt[i][j] = 1LL * cnt[i][j] * cnt[i - 1][j] % mod;
			cnt2[i][j] = 1LL * cnt2[i][j] * cnt2[i - 1][j] % mod2;
		}
	}

	FWT_xor(cnt[ccnt], -1, mod);
	FWT_xor(cnt2[ccnt], -1, mod2);
	for (int i = 0; i < maxn; i++) {
		if (cnt[ccnt][i] != 0 || cnt2[ccnt][i] != 0) {
			printf("%d %lld\n", i, cnt[ccnt][i]);
			break;
		}
	}
	return 0;
}