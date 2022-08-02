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
int n, k;

vector< long long > A, B;
const int mod = 1e9 + 7;

long long quick(long long a, long long b) {
	long long res = 1;
	while (b) {
		if (b % 2) res = res * a % mod;
		b /= 2;
		a = a * a % mod;
	}
	return res;
}

void init() {
	A.resize(n);
	B.resize(n);
	A[0] = 1;
	for (int i = 1; i <= n - 1; i++) {
		A[i] = A[i - 1] * i % mod;
	}
	B[n - 1] = quick(A[n - 1], mod - 2);
	for (int i = n - 2; i >= 0; i--) {
		B[i] = B[i + 1] * (i + 1) % mod;
	}
}

long long C(int a, int b) {
	return A[a] * B[b] % mod * B[a - b] % mod;
}

int main() {
#ifdef LOCAL
	freopen("data.in", "r", stdin);
#endif
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n >> k;
	string s;
	cin >> s;
	if (n == 1) {
		cout << s << endl;
		return 0;
	}

	init();
	vector< int > num(n + 1);
	for (int i = 1; i <= n; i++) {
		num[i] = s[i - 1] - '0';
	}

	if (k == 0) {
		long long res = 0;
		for (int i = 1; i <= n; i++) {
			res = (res * 10 % mod + num[i]) % mod;
		}
		cout << res << endl;
		return 0;
	}

	vector< int > sum(n + 1, 0);
	for (int i = 1; i <= n; i++) {
		sum[i] = (sum[i - 1] + num[i]) % mod;
	}
	long long res = 0;
	long long ten = 1;
	for (int j = 1; j <= n - k; j++) {
		int i = n - j;
		res = (res + C(n - 1 - j, k - 1) * ten % mod * sum[i] % mod) % mod;
		ten = ten * 10 % mod;
	}
	debug(res);

	ten = 1;
	long long val = 0;
	for (int i = n; i > k; i--) {
		val = (num[i] * ten % mod + val) % mod;
		ten = ten * 10 % mod;
		res = (res + C(i - 2, k - 1) * val % mod) % mod;
	}

	cout << res << endl;
	return 0;
}