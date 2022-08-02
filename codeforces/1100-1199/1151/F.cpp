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
const int maxn = 101;

struct Matrix {
	int n, m;
	int mat[maxn][maxn];

	Matrix(int _n, int _m) {
		n = _n, m = _m;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				mat[i][j] = 0;
			}
		}
	}

	Matrix operator*(const Matrix& b) const {
		assert(m == b.n);
		Matrix res(n, b.m);
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < b.m; j++) {
				for (int k = 0; k < m; k++) {
					int tmp = 1LL * mat[i][k] * b.mat[k][j] % mod;
					res.mat[i][j] = (res.mat[i][j] + tmp) % mod;
				}
			}
		}
		return res;
	}
};

Matrix quick(Matrix& a, int b) {
	Matrix res(a.n, a.n);
	for (int i = 0; i < a.n; i++) {
		res.mat[i][i] = 1;
	}
	while (b) {
		if (b % 2) res = res * a;
		b /= 2;
		a = a * a;
	}
	return res;
}

int quick(int a, int b) {
	int res = 1;
	while (b) {
		if (b % 2) res = 1LL * res * a % mod;
		b /= 2;
		a = 1LL * a * a % mod;
	}
	return res;
}

int main() {
#ifdef LOCAL
	freopen("data.in", "r", stdin);
#endif
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n, k;
	cin >> n >> k;
	vector< int > a(n + 1);
	int zero = 0;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		if (a[i] == 0) {
			zero++;
		}
	}

	int have = 0;
	for (int i = 1; i <= zero; i++) {
		if (a[i] == 0) {
			have++;
		}
	}

	Matrix A(zero + 1, zero + 1);
	int mi = max(0, zero - (n - zero));

	for (int i = 0; i <= zero; i++) {
		//(i, i), (i, i - 1), (i, i + 1)
		if (i - 1 >= 0 && i - 1 >= mi) {
			A.mat[i][i - 1] = (zero - (i - 1)) * (zero - (i - 1));
		}
		if (i + 1 <= zero && i + 1 >= mi) {
			A.mat[i][i + 1] = (i + 1) * (n - 2 * zero + (i + 1)) % mod;
		}
		if (i >= mi)
			A.mat[i][i] = n * (n - 1) / 2 - (zero - i) * (zero - i) - i * (n - 2 * zero + i);
	}

	Matrix B(zero + 1, 1);
	B.mat[have][0] = 1;

	Matrix C = quick(A, k);

	Matrix D = C * B;

	int up = D.mat[zero][0];
	int down = 0;
	for (int i = 0; i <= zero; i++) {
		(down += D.mat[i][0]) %= mod;
	}
	debug(up, down);
	cout << 1LL * up * quick(down, mod - 2) % mod << endl;
	return 0;
}