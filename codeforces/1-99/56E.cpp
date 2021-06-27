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
typedef pair< pii, int > piii;
piii dom[maxn];
int dp[maxn];
int ans[maxn];

#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1

int mx[maxn << 2];

void push_up(int rt) {
	mx[rt] = max(mx[rt << 1], mx[rt << 1 | 1]);
}

void build(int l, int r, int rt) {
	if (l == r) {
		mx[rt] = 0;
		return;
	}
	int m = l + r >> 1;
	build(lson);
	build(rson);
}

void update(int L, int val, int l, int r, int rt) {
	if (l == r) {
		mx[rt] = val;
		return;
	}
	int m = l + r >> 1;
	if (L <= m)
		update(L, val, lson);
	else
		update(L, val, rson);
	push_up(rt);
}

int query(int L, int R, int l, int r, int rt) {
	if (L <= l && r <= R) {
		return mx[rt];
	}
	int res = 0;
	int m = l + r >> 1;
	if (L <= m) {
		res = max(res, query(L, R, lson));
	}
	if (R > m) {
		res = max(res, query(L, R, rson));
	}
	return res;
}

int main() {
	freopen("data.in", "r", stdin);
	int n;
	scanf("%d", &n);
	int x, h;
	for (int i = 1; i <= n; i++) {
		scanf("%d %d", &x, &h);
		dom[i] = { { x, h }, i };
	}
	sort(dom + 1, dom + 1 + n);
	set< pii > S;
	dp[n] = 1;
	ans[dom[n].second] = 1;
	S.insert({ dom[n].first.first, n });
	build(1, n, 1);
	update(n, n, 1, n, 1);
	for (int i = n - 1; i >= 1; i--) {
		int go = dom[i].first.first + dom[i].first.second - 1;
		debug(i, go);
		auto it = S.upper_bound({ go, n + 10 });
		if (it == S.begin()) {
			dp[i] = 1;
			update(i, i, 1, n, 1);
		} else {
			it--;
			int mx = query(i + 1, n, 1, n, 1);
			dp[i] = mx - i + 1;
			update(i, mx, 1, n, 1);
		}
		S.insert({ dom[i].first.first, i });
		ans[dom[i].second] = dp[i];
		debug(i, dp[i]);
	}
	for (int i = 1; i <= n; i++) {
		printf("%d ", ans[i]);
	}
	puts("");
	return 0;
}