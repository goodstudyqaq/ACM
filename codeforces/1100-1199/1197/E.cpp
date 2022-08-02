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
const int maxn2 = 4e5 + 5;
const int mod = 1e9 + 7;
const long long inf = 2e14 + 1;
// sum 是最小值的个数
long long mi[maxn2 << 2];
int sum[maxn2 << 2];

#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1

void push_up(int rt) {
	mi[rt] = min(mi[rt << 1], mi[rt << 1 | 1]);
	sum[rt] = 0;
	if (mi[rt] == mi[rt << 1]) {
		sum[rt] = (sum[rt] + sum[rt << 1]) % mod;
	}
	if (mi[rt] == mi[rt << 1 | 1]) {
		sum[rt] = (sum[rt] + sum[rt << 1 | 1]) % mod;
	}
}

void build(int l, int r, int rt) {
	if (l == r) {
		mi[rt] = inf;
		sum[rt] = 0;
		return;
	}
	int m = l + r >> 1;
	build(lson);
	build(rson);
	push_up(rt);
}

void update(int L, long long val, int num, int l, int r, int rt) {
	if (l == r) {
		if (mi[rt] == inf) {
			mi[rt] = val;
			sum[rt] = num;
		} else {
			if (val < mi[rt]) {
				mi[rt] = val;
				sum[rt] = num;
			} else if (val == mi[rt]) {
				sum[rt] = (sum[rt] + num) % mod;
			}
		}
		return;
	}
	int m = l + r >> 1;
	if (L <= m)
		update(L, val, num, lson);
	else
		update(L, val, num, rson);
	push_up(rt);
}

typedef pair< long long, long long > pll;
// 询问最小值
pll query1(int L, int R, int l, int r, int rt) {
	if (L <= l && r <= R) {
		return { mi[rt], sum[rt] };
	}
	int m = l + r >> 1;
	pll res1 = { inf, 0 }, res2 = { inf, 0 };
	if (L <= m) {
		res1 = query1(L, R, lson);
	}
	if (R > m) {
		res2 = query1(L, R, rson);
	}
	if (res1.first < res2.first)
		return res1;
	else if (res1.first > res2.first)
		return res2;
	return { res1.first, (res1.second + res2.second) % mod };
}

vector< pll > V;
vector< int > x;
int xcnt;

int main() {
#ifdef LOCAL
	freopen("data.in", "r", stdin);
#endif
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n;
	cin >> n;
	V.resize(n + 1);
	x.resize(n * 2);
	for (int i = 1; i <= n; i++) {
		cin >> V[i].first >> V[i].second;
		x[xcnt++] = V[i].first;
		x[xcnt++] = V[i].second;
	}

	sort(V.begin() + 1, V.begin() + 1 + n);

	sort(x.begin(), x.begin() + xcnt);
	xcnt = unique(x.begin(), x.begin() + xcnt) - x.begin();
	build(1, xcnt, 1);

	for (int i = n; i >= 1; i--) {
		auto it = V[i];
		long long val1 = it.first;
		long long val2 = it.second;
		int val1_idx = lower_bound(x.begin(), x.begin() + xcnt, val1) - x.begin() + 1;
		int val2_idx = lower_bound(x.begin(), x.begin() + xcnt, val2) - x.begin() + 1;

		// 找最小值
		pll the_mi = query1(val1_idx, xcnt, 1, xcnt, 1);

		if (the_mi.first == inf) {
			the_mi.first = val2;
			the_mi.second = 1;
		} else {
			the_mi.first = the_mi.first - val1 + val2;
		}
		update(val2_idx, the_mi.first, the_mi.second, 1, xcnt, 1);
	}

	cout << query1(1, xcnt, 1, xcnt, 1).second << endl;
	return 0;
}