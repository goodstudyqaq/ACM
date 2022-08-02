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

const int maxn = 3e5 + 5;
const int maxm = 1e6 + 5;
int mx[maxm << 2], lazy[maxm << 2];

#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1

void push_down(int rt) {
	if (lazy[rt]) {
		mx[rt << 1] += lazy[rt];
		mx[rt << 1 | 1] += lazy[rt];
		lazy[rt << 1] += lazy[rt];
		lazy[rt << 1 | 1] += lazy[rt];
		lazy[rt] = 0;
	}
}

void push_up(int rt) {
	mx[rt] = max(mx[rt << 1], mx[rt << 1 | 1]);
}

void update(int L, int R, int val, int l, int r, int rt) {
	if (L <= l && r <= R) {
		mx[rt] += val;
		lazy[rt] += val;
		return;
	}
	int m = l + r >> 1;
	push_down(rt);
	if (L <= m) {
		update(L, R, val, lson);
	}
	if (R > m) {
		update(L, R, val, rson);
	}
	push_up(rt);
}

int query(int l, int r, int rt) {
	if (l == r) {
		return l;
	}
	push_down(rt);
	int m = l + r >> 1;
	if (mx[rt << 1 | 1] > 0) {
		return query(rson);
	} else {
		return query(lson);
	}
}

int a[maxn], b[maxn];
int main() {
	freopen("data.in", "r", stdin);
	int n, m;
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
		update(1, a[i], 1, 1, maxm, 1);
	}
	for (int i = 1; i <= m; i++) {
		scanf("%d", &b[i]);
		update(1, b[i], -1, 1, maxm, 1);
	}
	debug(query(1, maxm, 1));
	int q;
	scanf("%d", &q);
	while (q--) {
		int opt, idx, val;
		scanf("%d %d %d", &opt, &idx, &val);
		if (opt == 1) {
			update(1, a[idx], -1, 1, maxm, 1);
			a[idx] = val;
			update(1, a[idx], 1, 1, maxm, 1);
		} else {
			update(1, b[idx], 1, 1, maxm, 1);
			b[idx] = val;
			update(1, b[idx], -1, 1, maxm, 1);
		}

		if (mx[1] > 0) {
			printf("%d\n", query(1, maxm, 1));
		} else {
			puts("-1");
		}
	}
	return 0;
}