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
const int maxn = 2e5 + 1;
struct node {
	int l, r;
};
vector< node > V;
vector< int > x;
int xcnt;

long long quick(long long a, long long b) {
	long long res = 1;
	while (b) {
		if (b % 2) res = res * a % mod;
		b /= 2;
		a = a * a % mod;
	}
	return res;
}

long long inv(long long a) {
	return quick(a, mod - 2);
}

long long A[maxn], B[maxn];

void init() {
	A[0] = 1;
	for (int i = 1; i < maxn; i++) {
		A[i] = A[i - 1] * i % mod;
	}
	B[maxn - 1] = inv(A[maxn - 1]);
	for (int i = maxn - 2; i >= 0; i--) {
		B[i] = B[i + 1] * (i + 1) % mod;
	}
}

long long C(int a, int b) {
	return A[a] * B[b] % mod * B[a - b] % mod;
}

long long ans;

int n, k;

int main() {
#ifdef LOCAL
	freopen("data.in", "r", stdin);
#endif
	ios::sync_with_stdio(false);
	cin.tie(0);
	init();
	cin >> n >> k;
	V.resize(n + 1);
	for (int i = 1; i <= n; i++) {
		int l, r;
		cin >> l >> r;
		V[i].l = l, V[i].r = r;
		x.push_back(l);
		x.push_back(r + 1);
	}

	sort(x.begin(), x.end());
	xcnt = unique(x.begin(), x.end()) - x.begin();

	vector< int > sum(xcnt + 1, 0);

	for (int i = 1; i <= n; i++) {
		int lidx = lower_bound(x.begin(), x.begin() + xcnt, V[i].l) - x.begin() + 1;
		int ridx = upper_bound(x.begin(), x.begin() + xcnt, V[i].r) - x.begin() + 1;
		sum[lidx] += 1;
		sum[ridx] -= 1;
	}

	for (int i = 1; i <= xcnt; i++) {
		sum[i] += sum[i - 1];
	}

	for (int i = 1; i <= xcnt; i++) {
		int val = sum[i];
		if (val < k) continue;
		int len = x[i] - x[i - 1];
		ans = (ans + C(val, k) * len % mod) % mod;
	}

	cout << ans << endl;
}