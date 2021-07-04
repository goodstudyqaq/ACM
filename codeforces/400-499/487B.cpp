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
typedef pair< int, int > pii;
int mi[maxn][20], mx[maxn][20];

int n, s, l;
void init() {
	for (int j = 1; j < 20; j++) {
		for (int i = 1; i <= n; i++) {
			int go = i + (1 << j) - 1;
			if (go <= n) {
				mi[i][j] = min(mi[i][j - 1], mi[i + (1 << (j - 1))][j - 1]);
				mx[i][j] = max(mx[i][j - 1], mx[i + (1 << (j - 1))][j - 1]);
			}
		}
	}
}

pii query2(int l, int r) {
	int k = log2(r - l + 1);
	return { min(mi[l][k], mi[r - (1 << k) + 1][k]), max(mx[l][k], mx[r - (1 << k) + 1][k]) };
}

#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1

int mi2[maxn << 2];
void update(int L, int val, int l, int r, int rt) {
	if (l == r) {
		mi2[rt] = val;
		return;
	}
	int m = l + r >> 1;
	if (L <= m) {
		update(L, val, lson);
	} else {
		update(L, val, rson);
	}
	mi2[rt] = min(mi2[rt << 1], mi2[rt << 1 | 1]);
}

int query(int L, int R, int l, int r, int rt) {
	if (L <= l && r <= R) {
		return mi2[rt];
	}
	int m = l + r >> 1;
	int res = 1e9;
	if (L <= m) {
		res = min(res, query(L, R, lson));
	}
	if (R > m) {
		res = min(res, query(L, R, rson));
	}
	return res;
}

int getl(int idx) {
	int left = 1, right = idx - l + 1;
	int ans = -1;
	while (left <= right) {
		int mid = left + right >> 1;
		auto it = query2(mid, idx);
		if (it.second - it.first <= s) {
			ans = mid;
			right = mid - 1;
		} else {
			left = mid + 1;
		}
	}
	return ans;
}

int main() {
	freopen("data.in", "r", stdin);
	scanf("%d %d %d", &n, &s, &l);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &mi[i][0]);
		mx[i][0] = mi[i][0];
	}
	init();
	update(0, 0, 0, n, 1);
	for (int i = 1; i <= n - 1; i++) {
		update(i, 1e9, 0, n, 1);
	}
	int res = -1;

	for (int i = l; i <= n; i++) {
		int r = i - l + 1;
		int l = getl(i);
		if (l == -1) {
			res = 1e9;
			continue;
		}
		res = query(l - 1, r - 1, 0, n, 1) + 1;

		debug(i, l, r, res);
		update(i, res, 0, n, 1);
	}
	if (res > n) res = -1;
	cout << res << endl;
}