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

vector< vector< int > > b;

int n, k;

int rmq_query(int l, int r) {
	int tmp_k = log2(r - l + 1);
	return min(b[l][tmp_k], b[r - (1 << tmp_k) + 1][tmp_k]);
}
vector< int > mn, lazy;
vector< int > lson, rson;
int ncnt;

void init() {
	for (int j = 1; (1 << j) <= n; j++) {
		for (int i = 1; i + (1 << j) - 1 <= n; i++) {
			b[i][j] = min(b[i][j - 1], b[i + (1 << (j - 1))][j - 1]);
		}
	}
	mn[++ncnt] = rmq_query(1, n);
}

int query(int l, int r) {
	if (r - l + 1 >= n) {
		return rmq_query(1, n);
	}
	l = (l - 1) % n + 1;
	r = (r - 1) % n + 1;
	if (l <= r) {
		return rmq_query(l, r);
	}
	return min(rmq_query(l, n), rmq_query(1, r));
}

void push_down(int l, int r, int rt) {
	if (lson[rt] == 0) {
		lson[rt] = ++ncnt;
	}
	if (rson[rt] == 0) {
		rson[rt] = ++ncnt;
	}
	int m = l + r >> 1;

	// lazy[rt] = 0 为默认状态，即需要更新子节点的 mn 和 lazy。 = -1 为已更新完状态。等于其他正整数为真正的 lazy，也同样需要往下传
	if (lazy[rt] != -1) {
		lazy[lson[rt]] = lazy[rt];
		lazy[rson[rt]] = lazy[rt];
		mn[lson[rt]] = lazy[lson[rt]] ? lazy[lson[rt]] : query(l, m);
		mn[rson[rt]] = lazy[rson[rt]] ? lazy[rson[rt]] : query(m + 1, r);
	}
	lazy[rt] = -1;
}

void update(int L, int R, int x, int l, int r, int rt) {
	if (L <= l && r <= R) {
		debug(l, r, rt, x);
		mn[rt] = lazy[rt] = x;
		return;
	}
	push_down(l, r, rt);
	int m = l + r >> 1;
	if (L <= m) {
		update(L, R, x, l, m, lson[rt]);
	}
	if (R > m) {
		update(L, R, x, m + 1, r, rson[rt]);
	}
	mn[rt] = min(mn[lson[rt]], mn[rson[rt]]);
}

int query(int L, int R, int l, int r, int rt) {
	if (L <= l && r <= R) {
		// debug(l, r, mn[rt]);
		return mn[rt];
	}
	push_down(l, r, rt);
	int m = l + r >> 1;
	int ans = 1e9 + 1;
	if (L <= m) {
		ans = min(ans, query(L, R, l, m, lson[rt]));
	}
	if (R > m) {
		ans = min(ans, query(L, R, m + 1, r, rson[rt]));
	}
	return ans;
}

int main() {
#ifdef LOCAL
	freopen("data.in", "r", stdin);
#endif
	ios::sync_with_stdio(false);
	cin.tie(0);

	cin >> n >> k;
	mn.resize((100000 + 10) * 60);
	lazy.resize((100000 + 10) * 60);
	lson.resize((100000 + 10) * 60);
	rson.resize((100000 + 10) * 60);
	b.resize(n + 1, vector< int >(17, 0));

	for (int i = 1; i <= n; i++) {
		cin >> b[i][0];
	}
	init();

	int q;
	cin >> q;
	while (q--) {
		debug(q);
		int opt, l, r, x;
		cin >> opt;
		if (opt == 1) {
			cin >> l >> r >> x;
			update(l, r, x, 1, n * k, 1);
		} else {
			cin >> l >> r;
			cout << query(l, r, 1, n * k, 1) << '\n';
		}
	}
	return 0;
}