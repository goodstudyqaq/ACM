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
const int maxn = 5e5 + 5;
long long a[maxn];
long long x[maxn];
int xcnt;
typedef pair< int, int > pii;
pii edge[maxn];

vector< pii > V[maxn];
int f[maxn];

int find(int u) {
	return u == f[u] ? u : f[u] = find(f[u]);
}

int reset(int idx) {
	set< int > S;
	for (auto e : V[idx]) {
		S.insert(e.first);
		S.insert(e.second);
		f[e.first] = e.first;
		f[e.second] = e.second;
	}
	return S.size();
}

long long quick(long long a, long long b) {
	long long res = 1;
	while (b) {
		if (b % 2) res = res * a % mod;
		b /= 2;
		a = a * a % mod;
	}
	return res;
}

int main() {
	freopen("data.in", "r", stdin);
	int n, m, k;
	scanf("%d %d %d", &n, &m, &k);
	for (int i = 1; i <= n; i++) {
		scanf("%lld", &a[i]);
	}

	int u, v;
	for (int i = 1; i <= m; i++) {
		scanf("%d %d", &u, &v);
		edge[i] = { u, v };
		x[xcnt++] = a[u] ^ a[v];
	}

	sort(x, x + xcnt);
	xcnt = unique(x, x + xcnt) - x;

	for (int i = 1; i <= m; i++) {
		u = edge[i].first, v = edge[i].second;
		long long tmp = a[u] ^ a[v];
		int idx = lower_bound(x, x + xcnt, tmp) - x;
		idx++;
		V[idx].push_back({ u, v });
	}

	long long res = 0;
	for (int i = 1; i <= xcnt; i++) {
		int cnt = reset(i);
		for (auto e : V[i]) {
			u = e.first, v = e.second;
			int fu = find(u);
			int fv = find(v);
			f[fu] = fv;
		}
		set< int > S;
		for (auto e : V[i]) {
			u = e.first;
			S.insert(find(u));
		}
		int cnt2 = S.size();
		int val = n - cnt + cnt2;
		res = (res + quick(2, val)) % mod;
	}

	res = (res + ((quick(2, k) - xcnt) % mod + mod) % mod * quick(2, n) % mod) % mod;
	cout << res << endl;
}