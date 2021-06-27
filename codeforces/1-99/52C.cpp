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
const long long inf = 1e15;

long long mi[maxn << 2];
long long lazy[maxn << 2];
long long a[maxn];
void push_up(int rt) {
	mi[rt] = min(mi[rt << 1], mi[rt << 1 | 1]);
}

void push_down(int rt) {
	if (lazy[rt]) {
		mi[rt << 1] += lazy[rt];
		mi[rt << 1 | 1] += lazy[rt];
		lazy[rt << 1] += lazy[rt];
		lazy[rt << 1 | 1] += lazy[rt];
		lazy[rt] = 0;
	}
}

void build(int l, int r, int rt) {
	if (l == r) {
		mi[rt] = a[l];
		return;
	}
	int m = l + r >> 1;
	build(lson);
	build(rson);
	push_up(rt);
}

void update(int L, int R, long long val, int l, int r, int rt) {
	if (L <= l && r <= R) {
		mi[rt] += val;
		lazy[rt] += val;
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

long long query(int L, int R, int l, int r, int rt) {
	if (L <= l && r <= R) {
		return mi[rt];
	}
	push_down(rt);
	int m = l + r >> 1;
	long long res = inf;
	if (L <= m) {
		res = min(res, query(L, R, lson));
	}
	if (R > m) {
		res = min(res, query(L, R, rson));
	}
	return res;
}

vector< int > v;

void read() {
	v.clear();
	int num;
	cin >> num;
	v.push_back(num + 1);
	while (cin.get() != '\n') {
		cin >> num;
		v.push_back(num + 1);
	}
}

int main() {
	freopen("data.in", "r", stdin);
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n;
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
	}
	build(1, n, 1);
	int m;
	cin >> m;
	while (m--) {
		read();
		if (v.size() == 2) {
			long long res = inf;
			if (v[0] <= v[1]) {
				res = query(v[0], v[1], 1, n, 1);
				cout << res << endl;
			} else {
				res = min(query(v[0], n, 1, n, 1), query(1, v[1], 1, n, 1));
				cout << res << endl;
			}
		} else {
			if (v[0] <= v[1]) {
				update(v[0], v[1], v[2] - 1, 1, n, 1);
			} else {
				update(v[0], n, v[2] - 1, 1, n, 1);
				update(1, v[1], v[2] - 1, 1, n, 1);
			}
		}
	}
	return 0;
}