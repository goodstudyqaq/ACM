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
const int mod2 = 1e9 + 6;

struct Matrix {
	int n;
	int mat[5][5];

	Matrix(int _n) {
		n = _n;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				mat[i][j] = 0;
			}
		}
	}

	Matrix operator*(const Matrix& b) const {
		Matrix res(n);
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				for (int k = 0; k < n; k++) {
					int tmp = 1LL * mat[i][k] * b.mat[k][j] % mod2;
					res.mat[i][j] = (res.mat[i][j] + tmp) % mod2;
				}
			}
		}
		return res;
	}
};

Matrix quick(Matrix a, long long b) {
	Matrix res(a.n);
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

int quick2(int a, int b) {
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
	long long n;
	int f1, f2, f3, c;
	cin >> n >> f1 >> f2 >> f3 >> c;

	Matrix a(3);
	a.mat[0][0] = a.mat[0][1] = a.mat[0][2] = a.mat[1][0] = a.mat[2][1] = 1;
	Matrix b(5);
	b.mat[0][0] = b.mat[0][1] = b.mat[0][2] = 1;
	b.mat[0][3] = 2;
	b.mat[0][4] = -4;
	b.mat[1][0] = 1;
	b.mat[2][1] = 1;
	b.mat[3][3] = b.mat[3][4] = 1;
	b.mat[4][4] = 1;

	long long res = 1;
	long long tmp_n = n - 3;
	Matrix tmp = quick(a, tmp_n);

	int val_f3 = quick2(f3, tmp.mat[0][0]);
	int val_f2 = quick2(f2, tmp.mat[0][1]);
	int val_f1 = quick2(f1, tmp.mat[0][2]);

	debug(val_f3, val_f2, val_f1);
	debug(tmp.mat[0][0], tmp.mat[0][1], tmp.mat[0][2]);
	res = res * val_f3 % mod * val_f2 % mod * val_f1 % mod;

	tmp = quick(b, tmp_n);
	int val_c = quick2(c, ((1LL * tmp.mat[0][3] * 3 % mod2 + tmp.mat[0][4]) % mod2 + mod2) % mod2);
	debug(res);
	res = res * val_c % mod;
	cout << res << endl;
	return 0;
}