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
const int maxm = maxn * 2;
int lazy[maxm << 2], lazy2[maxm << 2], mi1[maxm << 2], mi2[maxm << 2];

#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1

void push_up(int rt) {
	if (mi1[rt << 1] == -1) {
		mi1[rt] = mi1[rt << 1 | 1];
	} else {
		mi1[rt] = mi1[rt << 1];
	}

	if (mi2[rt << 1] == -1) {
		mi2[rt] = mi2[rt << 1 | 1];
	} else {
		mi2[rt] = mi2[rt << 1];
	}
}
//ok

void push_down(int rt, int l, int r) {
	int m = l + r >> 1;

	if (lazy[rt] == 1 || lazy[rt] == 2) {
		if (lazy[rt] == 1) {
			mi1[rt << 1] = l;
			mi2[rt << 1] = -1;
			mi1[rt << 1 | 1] = m + 1;
			mi2[rt << 1 | 1] = -1;
			lazy[rt << 1] = 1;
			lazy[rt << 1 | 1] = 1;
			lazy[rt] = 0;
		} else {
			mi1[rt << 1] = -1;
			mi2[rt << 1] = l;
			mi1[rt << 1 | 1] = -1;
			mi2[rt << 1 | 1] = m + 1;
			lazy[rt << 1] = lazy[rt << 1 | 1] = 2;
			lazy[rt] = 0;
		}
		lazy2[rt << 1] = lazy2[rt << 1 | 1] = 0;
	}

	if (lazy2[rt]) {
		swap(mi1[rt << 1], mi2[rt << 1]);
		swap(mi1[rt << 1 | 1], mi2[rt << 1 | 1]);
		lazy2[rt << 1] = !lazy2[rt << 1];
		lazy2[rt << 1 | 1] = !lazy2[rt << 1 | 1];
		lazy2[rt] = 0;
	}
}

void build(int l, int r, int rt) {
	if (l == r) {
		lazy[rt] = lazy2[rt] = 0;
		mi1[rt] = -1;
		mi2[rt] = l;
		return;
	}
	int m = l + r >> 1;
	build(lson);
	build(rson);
	push_up(rt);
}

void update(int L, int R, int v, int l, int r, int rt) {
	if (L <= l && r <= R) {
		if (v == 1) {
			mi1[rt] = l;
			mi2[rt] = -1;
			lazy[rt] = 1;
			lazy2[rt] = 0;
			return;
		} else if (v == 2) {
			mi1[rt] = -1;
			mi2[rt] = l;
			lazy[rt] = 2;
			lazy2[rt] = 0;
			return;
		} else {
			swap(mi1[rt], mi2[rt]);
			lazy2[rt] = lazy2[rt] ^ 1;
			return;
		}
	}
	push_down(rt, l, r);
	int m = l + r >> 1;
	if (L <= m) {
		update(L, R, v, lson);
	}
	if (R > m) {
		update(L, R, v, rson);
	}
	push_up(rt);
}

long long x[maxm], xcnt;

struct node {
	long long t, l, r;
	node(long long _t, long long _l, long long _r)
		: t(_t), l(_l), r(_r) {}
	node() {}
} nodes[maxn];

void out2(int l, int r, int rt) {
	if (l == r) {
		debug(l, r, rt, mi1[rt], mi2[rt], lazy[rt]);
		return;
	}
	// push_down(rt, l, r);
	debug(l, r, rt, mi1[rt], mi2[rt], lazy[rt]);
	int m = l + r >> 1;
	out2(lson);
	out2(rson);
	// push_up(rt);
}

void out() {
	out2(1, xcnt, 1);
}

int main() {
	freopen("data.in", "r", stdin);
	int n;
	scanf("%d", &n);
	long long t, l, r;
	for (int i = 1; i <= n; i++) {
		scanf("%lld %lld %lld", &t, &l, &r);
		nodes[i] = node(t, l, r);
		x[xcnt++] = l;
		x[xcnt++] = r + 1;
	}
	x[xcnt++] = 1;

	sort(x, x + xcnt);
	xcnt = unique(x, x + xcnt) - x;
	debug(xcnt);
	build(1, xcnt, 1);
	for (int i = 1; i <= n; i++) {

		int lidx = lower_bound(x, x + xcnt, nodes[i].l) - x;
		int ridx = upper_bound(x, x + xcnt, nodes[i].r) - x;
		update(lidx + 1, ridx, nodes[i].t, 1, xcnt, 1);

		debug(i, nodes[i].t, lidx + 1, ridx, mi2[1]);
		printf("%lld\n", x[mi2[1] - 1]);
	}
	return 0;
}