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

const int maxn = 2e5 + 5;
long long d[maxn], h[maxn];
long long R[maxn][20], L[maxn][20];
int idx[maxn][20], idx2[maxn][20];
void init(int num) {
	for (int j = 1; j < 20; j++) {
		for (int i = 1; i <= num; i++) {
			if (i + (1 << j) - 1 <= num) {
				R[i][j] = max(R[i][j - 1], R[i + (1 << (j - 1))][j - 1]);
				L[i][j] = max(L[i][j - 1], L[i + (1 << (j - 1))][j - 1]);
				if (R[i][j] == R[i][j - 1]) {
					idx[i][j] = idx[i][j - 1];
				} else {
					idx[i][j] = idx[i + (1 << (j - 1))][j - 1];
				}
				if (L[i][j] == L[i][j - 1]) {
					idx2[i][j] = idx2[i][j - 1];
				} else {
					idx2[i][j] = idx2[i + (1 << (j - 1))][j - 1];
				}
			}
		}
	}
}

pair< long long, int > qmax1(int i, int j) {
	if (i > j) return { -1e18, 0 };
	int k = log2(j - i + 1);
	if (R[i][k] > R[j - (1 << k) + 1][k]) {
		return { R[i][k], idx[i][k] };
	}
	return { R[j - (1 << k) + 1][k], idx[j - (1 << k) + 1][k] };
}
pair< long long, int > qmax2(int i, int j) {
	if (i > j) return { -1e18, 0 };
	int k = log2(j - i + 1);
	if (L[i][k] > L[j - (1 << k) + 1][k]) {
		return { L[i][k], idx2[i][k] };
	}
	return { L[j - (1 << k) + 1][k], idx2[j - (1 << k) + 1][k] };
}

int main() {
	freopen("data1.in", "r", stdin);
	int n, m;
	scanf("%d %d", &n, &m);

	for (int i = 1; i <= n; i++) {
		scanf("%lld", &d[i]);
		d[i + n] = d[i];
	}
	for (int i = 1; i <= n; i++) {
		scanf("%lld", &h[i]);
		h[i + n] = h[i];
	}
	long long presum = 0;
	for (int i = 1; i <= 2 * n; i++) {
		R[i][0] = 2LL * h[i] + presum;
		L[i][0] = 2LL * h[i] - presum;
		idx[i][0] = i;
		idx2[i][0] = i;
		presum += d[i];
		debug(i, L[i][0], R[i][0]);
	}

	init(2 * n);
	int a, b;
	while (m--) {
		scanf("%d %d", &a, &b);
		int lidx, ridx;
		if (a <= b) {
			ridx = a + n - 1;
			lidx = b + 1;
		} else {
			ridx = a + n - 1;
			lidx = b + n + 1;
		}

		auto tmp1 = qmax1(lidx, ridx);
		auto tmp2 = qmax1(lidx, tmp1.second - 1);
		auto tmp3 = qmax1(tmp1.second + 1, ridx);
		vector< pair< long long, int > > V, V2;
		V = { tmp1, tmp2, tmp3 };

		auto tmp4 = qmax2(lidx, ridx);
		auto tmp5 = qmax2(lidx, tmp4.second - 1);
		auto tmp6 = qmax2(tmp4.second + 1, ridx);
		V2 = { tmp4, tmp5, tmp6 };
		long long res = -1e18;
		for (auto u : V) {
			for (auto v : V2) {
				if (u.second != v.second) {
					res = max(res, u.first + v.first);
				}
			}
		}
		printf("%lld\n", res);
	}
	return 0;
}