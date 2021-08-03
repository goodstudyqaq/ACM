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

const int maxn = 5e5 + 5;
const int limit = 5e5 + 1;
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1

int mi[maxn << 2], lazy[maxn << 2];

void push_down(int rt) {
	if (lazy[rt] != maxn) {
		mi[rt << 1] = min(mi[rt << 1], lazy[rt]);
		mi[rt << 1 | 1] = min(mi[rt << 1 | 1], lazy[rt]);
		lazy[rt << 1] = min(lazy[rt << 1], lazy[rt]);
		lazy[rt << 1 | 1] = min(lazy[rt << 1 | 1], lazy[rt]);
		lazy[rt] = maxn;
	}
}
void push_up(int rt) {
	mi[rt] = min(mi[rt << 1], mi[rt << 1 | 1]);
}

void build(int l, int r, int rt) {
	if (l == r) {
		mi[rt] = l;
		lazy[rt] = maxn;
		return;
	}
	int m = l + r >> 1;
	build(lson);
	build(rson);
	push_up(rt);
	lazy[rt] = maxn;
}
void update(int L, int R, int val, int l, int r, int rt) {
	if (L <= l && r <= R) {
		mi[rt] = min(mi[rt], val);
		lazy[rt] = min(lazy[rt], val);
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

int query(int L, int R, int l, int r, int rt) {
	if (L <= l && r <= R) {
		return mi[rt];
	}
	int m = l + r >> 1;
	push_down(rt);
	int res = maxn;
	if (L <= m) {
		res = min(res, query(L, R, lson));
	}
	if (R > m) {
		res = min(res, query(L, R, rson));
	}
	return res;
}
int query(int L, int l, int r, int rt) {
	if (l == r) {
		return mi[rt];
	}
	int m = l + r >> 1;
	push_down(rt);
	if (L <= m)
		return query(L, lson);
	else
		return query(L, rson);
}

int n, m;
vector< vector< int > > lxt;

void query(int l, int r, int rt) {
	if (l == r) {
		lxt[l][0] = mi[rt];
		return;
	}
	int m = l + r >> 1;
	push_down(rt);
	query(lson);
	query(rson);
}

vector< int > x;
int xcnt;
void init() {
	lxt.resize(xcnt + 1, vector< int >(20, 0));
	query(1, xcnt, 1);
	for (int j = 1; j < 20; j++) {
		for (int i = 1; i <= xcnt; i++) {
			int val = lxt[i][j - 1];
			if (val == 0) {
				lxt[i][j] = 0;
			} else {
				lxt[i][j] = lxt[val][j - 1];
			}
		}
	}
}

int query2(int idx, int k) {
	int go = idx;
	for (int i = 19; i >= 0; i--) {
		if ((k >> i) & 1) {
			go = lxt[go][i];
		}
	}
	return go;
}

int work(int lidx, int ridx) {
	if (query2(ridx, n) > lidx) return -1;
	int ans = 0;
	for (int i = 19; i >= 0; i--) {
		if (lxt[ridx][i] > lidx) {
			ridx = lxt[ridx][i];
			ans += (1 << i);
		}
	}
	if (ans == (1 << 20) - 1) return -1;
	return ans + 1;
}

typedef pair< int, int > pii;
vector< pii > line, querys;

int main() {
#ifdef LOCAL
	freopen("data.in", "r", stdin);
#endif
	ios::sync_with_stdio(false);
	cin.tie(0);

	cin >> n >> m;
	line.resize(n + 1);
	querys.resize(m + 1);
	for (int i = 1; i <= n; i++) {
		int l, r;
		cin >> l >> r;
		line[i] = { l + 1, r + 1 };
		x.emplace_back(l + 1);
		x.emplace_back(r + 1);
	}

	for (int i = 1; i <= m; i++) {
		int l, r;
		cin >> l >> r;
		querys[i] = { l + 1, r + 1 };
		x.emplace_back(l + 1);
		x.emplace_back(r + 1);
	}
	sort(x.begin(), x.end());
	xcnt = unique(x.begin(), x.end()) - x.begin();
	build(1, xcnt, 1);
	for (int i = 1; i <= n; i++) {
		int idx1 = lower_bound(x.begin(), x.begin() + xcnt, line[i].first) - x.begin() + 1;
		int idx2 = lower_bound(x.begin(), x.begin() + xcnt, line[i].second) - x.begin() + 1;
		debug(idx1, idx2);
		update(idx1, idx2, idx1, 1, xcnt, 1);
	}
	init();

	for (int i = 1; i <= m; i++) {
		int idx1 = lower_bound(x.begin(), x.begin() + xcnt, querys[i].first) - x.begin() + 1;
		int idx2 = lower_bound(x.begin(), x.begin() + xcnt, querys[i].second) - x.begin() + 1;
		int val = work(idx1, idx2);
		cout << val << endl;
	}

	return 0;
}