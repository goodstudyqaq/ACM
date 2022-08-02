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
const int mod = 1e9 + 7;
struct Matrix {
	int n;
	int mat[2][2];
	Matrix() {}
	Matrix(int _n) {
		n = _n;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				mat[i][j] = 0;
			}
		}
	}

	Matrix operator*(const Matrix& b) const {
		Matrix res = Matrix(n);
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				for (int k = 0; k < n; k++) {
					int tmp = 1LL * mat[i][k] * b.mat[k][j] % mod;
					res.mat[i][j] = (res.mat[i][j] + tmp) % mod;
				}
			}
		}
		return res;
	}

	Matrix operator+(const Matrix& b) const {
		Matrix res = Matrix(n);
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				int tmp = (mat[i][j] + b.mat[i][j]) % mod;
				res.mat[i][j] = tmp;
			}
		}
		return res;
	}

	bool operator==(const Matrix& b) const {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (mat[i][j] != b.mat[i][j]) return false;
			}
		}
		return true;
	}
};

Matrix quick_mul(Matrix a, int num) {
	Matrix e(a.n);
	for (int i = 0; i < e.n; i++) {
		e.mat[i][i] = 1;
	}
	Matrix tmp = a;
	while (num) {
		if (num % 2) e = e * tmp;
		num /= 2;
		tmp = tmp * tmp;
	}
	return e;
}

Matrix sum[maxn << 2], lazy[maxn << 2];
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
Matrix a;

Matrix cal(int val) {
	Matrix res(2);
	res.mat[0][0] = res.mat[0][1] = res.mat[1][0] = 1;
	res = quick_mul(res, val - 1);
	return res;
}

void push_up(int rt) {
	sum[rt] = sum[rt << 1] + sum[rt << 1 | 1];
}

void push_down(int rt) {
	if (lazy[rt] == a) {
		return;
	}
	sum[rt << 1] = sum[rt << 1] * lazy[rt];
	sum[rt << 1 | 1] = sum[rt << 1 | 1] * lazy[rt];
	lazy[rt << 1] = lazy[rt << 1] * lazy[rt];
	lazy[rt << 1 | 1] = lazy[rt << 1 | 1] * lazy[rt];
	lazy[rt] = a;
	return;
}

void build(int l, int r, int rt) {
	lazy[rt] = a;
	if (l == r) {
		int val;
		cin >> val;
		sum[rt] = cal(val);
		return;
	}
	int m = l + r >> 1;
	build(lson);
	build(rson);
	push_up(rt);
}

void update(int L, int R, Matrix val, int l, int r, int rt) {
	if (L <= l && r <= R) {
		sum[rt] = sum[rt] * val;
		lazy[rt] = lazy[rt] * val;
		return;
	}
	push_down(rt);
	int m = l + r >> 1;
	if (L <= m) {
		update(L, R, val, lson);
	}
	if (R > m) {
		update(L, R, val, rson);
	}
	push_up(rt);
}

Matrix query(int L, int R, int l, int r, int rt) {
	if (L <= l && r <= R) {
		return sum[rt];
	}
	push_down(rt);
	int m = l + r >> 1;
	Matrix res(2);
	if (L <= m) {
		res = res + query(L, R, lson);
	}
	if (R > m) {
		res = res + query(L, R, rson);
	}
	return res;
}

int main() {
#ifdef LOCAL
	freopen("data.in", "r", stdin);
#endif
	ios::sync_with_stdio(false);
	cin.tie(0);
	a.n = 2;
	a.mat[0][0] = a.mat[1][1] = 1;
	int n, m;
	cin >> n >> m;
	build(1, n, 1);
	while (m--) {
		int opt;
		cin >> opt;
		if (opt == 1) {
			int l, r, x;
			cin >> l >> r >> x;
			Matrix tmp(2);
			tmp.mat[0][0] = tmp.mat[0][1] = tmp.mat[1][0] = 1;
			tmp = quick_mul(tmp, x);
			update(l, r, tmp, 1, n, 1);
		} else {
			int l, r;
			cin >> l >> r;
			Matrix tmp = query(l, r, 1, n, 1);
			cout << tmp.mat[0][0] << '\n';
		}
	}
	return 0;
}