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
vector< int > A, B;

int quick(int a, int b) {
	int res = 1;
	while (b) {
		if (b % 2) res = 1LL * res * a % mod;
		b /= 2;
		a = 1LL * a * a % mod;
	}
	return res;
}

void init() {
	A.resize(2e5 + 1), B.resize(2e5 + 1);
	A[0] = 1;
	for (int i = 1; i <= 2e5; i++) {
		A[i] = 1LL * A[i - 1] * i % mod;
	}
	B[200000] = quick(A[200000], mod - 2);
	for (int i = 199999; i >= 0; i--) {
		B[i] = 1LL * B[i + 1] * (i + 1) % mod;
	}
}

int C(int a, int b) {
	if (a < 0 || b < 0) return 0;
	if (a < b) return 0;
	return 1LL * A[a] * B[b] % mod * B[a - b] % mod;
}

int n, l, r;
bool check(int idx, int val) {
	int left = l - idx;
	int right = r - idx;
	if (val <= right && -val >= left) return true;
	return false;
}

int main() {
#ifdef LOCAL
	freopen("data.in", "r", stdin);
#endif
	ios::sync_with_stdio(false);
	cin.tie(0);
	init();
	int T;
	cin >> T;
	while (T--) {
		cin >> n >> l >> r;
		int right = r - n;
		int left = l - 1;

		int mi = min(abs(left), abs(right));
		int res = 0;
		if (n % 2) {
			res = 1LL * C(n, n / 2) * 2 % mod * mi % mod;
		} else {
			res = 1LL * C(n, n / 2) * mi % mod;
		}
		// debug(res);
		int mi2 = min(abs(l - n), abs(r - 1));
		int left_idx = 1, right_idx = n;
		for (int i = mi + 1; i <= mi2; i++) {
			while (left_idx <= n && left_idx - i < l) left_idx++;
			while (right_idx >= 1 && right_idx + i > r) right_idx--;
			// debug(res);
			if (left_idx - right_idx > 1) break;
			int left_num = left_idx - 1;
			int right_num = n - right_idx;
			if (left_num > (n + 1) / 2 || right_num > (n + 1) / 2) break;
			int num = right_idx - left_idx + 1;
			// debug(i, left_idx, right_idx);
			if (n % 2) {
				int left_need = n / 2 - left_num;
				if (left_need >= 0) {
					int tmp = C(num, left_need);
					res = (res + tmp) % mod;
				}
				left_need = (n + 1) / 2 - left_num;
				int tmp = C(num, left_need);
				res = (res + tmp) % mod;
			} else {
				int left_need = n / 2 - left_num;
				// debug(num, left_need);
				int tmp = C(num, left_need);
				res = (res + tmp) % mod;
			}
		}
		cout << res << '\n';
	}
	return 0;
}