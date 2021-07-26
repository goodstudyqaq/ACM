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

vector< int > h, b;

#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1

const int maxn = 3e5 + 5;
const long long inf = 3e14 + 1;
long long mx[maxn << 2];

void update(int L, long long val, int l, int r, int rt) {
	if (l == r) {
		mx[rt] = val;
		return;
	}
	int m = l + r >> 1;
	if (L <= m) {
		update(L, val, lson);
	} else {
		update(L, val, rson);
	}
	mx[rt] = max(mx[rt << 1], mx[rt << 1 | 1]);
}

long long query(int L, int R, int l, int r, int rt) {
	if (L <= l && r <= R) {
		return mx[rt];
	}
	int m = l + r >> 1;
	long long res = -inf;
	if (L <= m) {
		res = max(res, query(L, R, lson));
	}
	if (R > m) {
		res = max(res, query(L, R, rson));
	}
	return res;
}

int main() {
#ifdef LOCAL
	freopen("data.in", "r", stdin);
#endif
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n;
	cin >> n;
	h.resize(n + 1);
	b.resize(n + 1);
	for (int i = 1; i <= n; i++) {
		cin >> h[i];
	}
	for (int i = 1; i <= n; i++) {
		cin >> b[i];
	}

	vector< int > st(n + 1);
	vector< int > laxt_small(n + 1);
	int now_idx = 0;
	for (int i = 1; i <= n; i++) {
		while (now_idx > 0 && h[st[now_idx - 1]] > h[i]) {
			now_idx--;
		}
		if (now_idx == 0) {
			laxt_small[i] = -1;
		} else {
			laxt_small[i] = st[now_idx - 1];
		}
		st[now_idx++] = i;
	}
	vector< long long > dp(n + 1, 0);
	for (int i = 1; i <= n; i++) {
		if (i == 1) {
			dp[1] = b[1];
			update(1, b[1], 0, n, 1);
		} else {
			int lxt_idx = laxt_small[i];
			if (lxt_idx == -1) {
				long long tmp = query(0, i - 1, 0, n, 1) + b[i];
				dp[i] = tmp;
				update(i, tmp, 0, n, 1);
			} else {
				long long tmp = dp[lxt_idx];
				tmp = max(tmp, query(lxt_idx, i - 1, 0, n, 1) + b[i]);
				dp[i] = tmp;
				update(i, tmp, 0, n, 1);
			}
		}
		debug(i, dp[i], laxt_small[i]);
	}
	cout << dp[n] << endl;
	return 0;
}