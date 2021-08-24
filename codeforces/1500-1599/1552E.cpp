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

const int maxn = 1e4 + 5;
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1

int mx[maxn << 2], lazy[maxn << 2];

void push_down(int rt) {
	if (lazy[rt]) {
		mx[rt << 1] += lazy[rt];
		mx[rt << 1 | 1] += lazy[rt];
		lazy[rt << 1] += lazy[rt];
		lazy[rt << 1 | 1] += lazy[rt];
		lazy[rt] = 0;
		return;
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

int query(int L, int R, int l, int r, int rt) {
	if (L <= l && r <= R) {
		return mx[rt];
	}
	push_down(rt);
	int m = l + r >> 1;
	int res = 0;
	if (L <= m) res = max(res, query(L, R, lson));
	if (R > m) res = max(res, query(L, R, rson));
	return res;
}
typedef pair< int, int > pii;

int main() {
#ifdef LOCAL
	freopen("data.in", "r", stdin);
#endif
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n, k;
	cin >> n >> k;
	vector< int > c(n * k + 1);
	for (int i = 1; i <= n * k; i++) {
		cin >> c[i];
	}

	vector< int > vis(n + 1, -1);
	vector< int > vis2(n + 1, 0);
	vector< pii > ans(n + 1);
	int m = n * k;
	int LIMIT = (n - 1) / (k - 1) + 1;
	for (int i = 1; i <= m; i++) {
		int val = c[i];
		if (vis2[val]) continue;
		if (vis[val] == -1) {
			vis[val] = i;
		} else {
			ans[val] = { vis[val], i };
			// ans.push_back({ vis[val], i });
			vis2[val] = 1;
			if (ans.size() == n) break;
			update(vis[val], i, 1, 1, m, 1);
			int tmp = query(vis[val], i, 1, m, 1);
			if (tmp >= LIMIT) {
				int now = i;
				while (now >= vis[val]) {
					int tmp2 = query(now, now, 1, m, 1);
					if (tmp2 >= LIMIT) break;
					now--;
				}
				for (int j = 1; j <= n; j++) {
					if (vis[j] != -1 && vis[j] <= now) vis[j] = -1;
				}
			}
		}
	}
	for (int i = 1; i <= n; i++) {
		auto it = ans[i];
		cout << it.first << ' ' << it.second << '\n';
	}
	return 0;
}