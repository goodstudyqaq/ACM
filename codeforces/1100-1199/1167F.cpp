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

const int maxn = 5e5 + 5;
const int mod = 1e9 + 7;
int a[maxn], b[maxn];
map< int, int > M;
long long t[maxn];
long long sum[maxn];
#define lowbit(x) x & -x

void add(int idx, long long v) {
	while (idx < maxn) {
		sum[idx] += v;
		idx += lowbit(idx);
	}
}

long long query(int idx) {
	long long res = 0;
	while (idx) {
		res += sum[idx];
		idx -= lowbit(idx);
	}
	return res;
}

int main() {
	int n;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
		b[i] = a[i];
	}
	sort(b + 1, b + 1 + n);
	for (int i = 1; i <= n; i++) {
		M[b[i]] = i;
	}

	for (int i = 1; i <= n; i++) {
		int idx = M[a[i]];
		long long tmp = query(idx) * (n - i + 1) % mod;
		t[i] = (t[i] + tmp) % mod;
		add(idx, i);
	}

	memset(sum, 0, sizeof(sum));

	for (int i = n; i >= 1; i--) {
		int idx = M[a[i]];
		long long tmp = query(idx) * i % mod;
		t[i] = (t[i] + tmp) % mod;
		add(idx, n - i + 1);
		t[i] = (t[i] + 1LL * i * (n - i + 1) % mod) % mod;
	}

	long long ans = 0;
	for (int i = 1; i <= n; i++) {
		ans = (ans + 1LL * a[i] * t[i] % mod) % mod;
	}
	cout << ans << endl;
	return 0;
}