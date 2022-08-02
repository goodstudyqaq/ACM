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
vector< int > h;
const int mod = 998244353;

long long quick(long long a, long long b) {
	long long res = 1;
	while (b) {
		if (b % 2) res = res * a % mod;
		a = a * a % mod;
		b /= 2;
	}
	return res;
}

vector< long long > A, B;

void init(int num) {
	A.resize(num + 1);
	B.resize(num + 1);
	A[0] = 1;
	for (int i = 1; i <= num; i++) {
		A[i] = A[i - 1] * i % mod;
	}
	B[num] = quick(A[num], mod - 2);
	for (int i = num - 1; i >= 0; i--) {
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
	h.resize(n + 1);
	for (int i = 1; i <= n; i++) {
		cin >> h[i];
	}

	if (k == 1) {
		cout << 0 << endl;
		return 0;
	}

	int num = 0;
	for (int i = 1; i <= n; i++) {
		int nxt = i % n + 1;
		if (h[i] != h[nxt]) num++;
	}

	if (num == 0) {
		cout << 0 << endl;
		return 0;
	}
	init(num);

	long long res = 0;
	for (int i = 0; i <= (num - 1) / 2; i++) {

		long long tmp1 = C(num, i);
		long long tmp2 = 0;

		for (int j = i + 1; i + j <= num; j++) {
			long long tmp3 = C(num - i, j) * quick(k - 2, num - i - j) % mod;
			tmp2 = (tmp2 + tmp3) % mod;
		}
		tmp1 = tmp1 * tmp2 % mod;
		res = (res + tmp1) % mod;
	}
	res = res * quick(k, n - num) % mod;
	cout << res << endl;
	return 0;
}