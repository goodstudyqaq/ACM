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
vector< int > b[maxn << 2];

#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1

void update(int L, int R, int val, int l, int r, int rt) {
	if (L <= l && r <= R) {
		b[rt].push_back(val);
		return;
	}
	int m = l + r >> 1;
	if (L <= m) {
		update(L, R, val, lson);
	}
	if (R > m) {
		update(L, R, val, rson);
	}
}

bitset< maxn > ans;

void work(bitset< maxn > now, int l, int r, int rt) {
	vector< int >& it = b[rt];
	for (int i = 0; i < it.size(); i++) {
		now |= (now << it[i]);
	}
	if (l == r) {
		ans |= now;
		return;
	}

	int m = l + r >> 1;
	work(now, lson);
	work(now, rson);
}

int main() {
#ifdef LOCAL
	freopen("data.in", "r", stdin);
#endif
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n, q;
	cin >> n >> q;
	for (int i = 1; i <= q; i++) {
		int l, r, w;
		cin >> l >> r >> w;
		update(l, r, w, 1, n, 1);
	}
	bitset< maxn > now;
	now[0] = 1;
	work(now, 1, n, 1);

	int res = 0;
	for (int i = 1; i <= n; i++) {
		if (ans[i]) {
			res++;
		}
	}
	cout << res << endl;
	for (int i = 1; i <= n; i++) {
		if (ans[i]) {
			cout << i << ' ';
		}
	}
	cout << endl;
}