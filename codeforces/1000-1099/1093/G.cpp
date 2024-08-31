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
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
const int maxn = 2e5 + 5;

int n, k;
int LIMIT;
struct node {
	vector< int > f;

	void merge(node& a) {
		for (int i = 0; i < LIMIT; i++) {
			f[i] = max(f[i], a.f[i]);
		}
	}

} nodes[maxn << 2];

void push_up(int rt) {
	for (int i = 0; i < LIMIT; i++) {
		nodes[rt].f[i] = max(nodes[rt << 1].f[i], nodes[rt << 1 | 1].f[i]);
	}
}

void work(int rt) {
	vector< int > a(k + 1);
	for (int i = 1; i <= k; i++) {
		cin >> a[i];
	}
	nodes[rt].f.resize(LIMIT);
	for (int i = 0; i < LIMIT; i++) {
		// 0 表示正， 1 表示负
		int val = 0;
		for (int j = 0; j < k; j++) {
			if ((i >> j) & 1) {
				val -= a[j + 1];
			} else {
				val += a[j + 1];
			}
		}
		nodes[rt].f[i] = val;
	}
}

void build(int l, int r, int rt) {
	// if (r != 0)
	nodes[rt].f.resize(LIMIT);
	if (l == r) {
		work(rt);
		return;
	}

	int m = l + r >> 1;
	build(lson);
	build(rson);
	push_up(rt);
}

void update(int L, int l, int r, int rt) {
	if (l == r) {
		work(rt);
		return;
	}
	int m = l + r >> 1;
	if (L <= m)
		update(L, lson);
	else
		update(L, rson);
	push_up(rt);
}

node query(int L, int R, int l, int r, int rt) {
	if (L <= l && r <= R) {
		return nodes[rt];
	}
	node res;
	res.f.resize(LIMIT, -1e7);

	int m = l + r >> 1;
	if (L <= m) {
		node tmp = query(L, R, lson);
		res.merge(tmp);
	}
	if (R > m) {
		node tmp = query(L, R, rson);
		res.merge(tmp);
	}
	return res;
}

int main() {
#ifdef LOCAL
	freopen("data.in", "r", stdin);
#endif
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n >> k;
	LIMIT = 1 << k;
	build(1, n, 1);
	debug("zz");
	int q;
	cin >> q;
	while (q--) {
		int opt;
		cin >> opt;
		if (opt == 1) {
			int idx;
			cin >> idx;
			update(idx, 1, n, 1);
		} else {
			int l, r;
			cin >> l >> r;
			node res = query(l, r, 1, n, 1);
			int ans = -1e7;
			for (int i = 0; i < LIMIT; i++) {
				ans = max(ans, res.f[i] + res.f[LIMIT - 1 - i]);
			}
			cout << ans << '\n';
		}
	}
	return 0;
}