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

int len;
struct Query {
	int l, r, idx;
	int block;
	Query(int _l, int _r, int _idx)
		: l(_l), r(_r), idx(_idx) {
		block = l / len;
	}
	Query() {}
	bool operator<(const Query& b) const {
		if (block != b.block) return block < b.block;
		return r < b.r;
	}
};

int main() {
#ifdef LOCAL
	freopen("data.in", "r", stdin);
#endif
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n, k;
	cin >> n >> k;
	len = sqrt(n);

	vector< int > t;
	vector< long long > a;
	t.resize(n + 1);
	a.resize(n + 1);
	for (int i = 1; i <= n; i++) {
		cin >> t[i];
	}
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		if (t[i] == 2) a[i] *= -1;
		a[i] += a[i - 1];
	}

	vector< long long > x(n + 1), y(n + 1), z(n + 1);
	vector< long long > u;
	for (int i = 0; i <= n; i++) {
		x[i] = a[i];
		y[i] = a[i] - k;
		z[i] = a[i] + k;
		u.push_back(x[i]);
		u.push_back(y[i]);
		u.push_back(z[i]);
	}
	sort(u.begin(), u.end());
	int unum = unique(u.begin(), u.end()) - u.begin();

	for (int i = 0; i <= n; i++) {
		x[i] = lower_bound(u.begin(), u.begin() + unum, x[i]) - u.begin();
		y[i] = lower_bound(u.begin(), u.begin() + unum, y[i]) - u.begin();
		z[i] = lower_bound(u.begin(), u.begin() + unum, z[i]) - u.begin();
	}

	int q;
	cin >> q;
	vector< Query > Q;
	for (int i = 1; i <= q; i++) {
		int l, r;
		cin >> l >> r;
		Q.push_back(Query(l - 1, r, i));
	}

	sort(Q.begin(), Q.end());

	vector< long long > ans(q + 1);
	vector< int > cnt(unum, 0);
	long long res = 0;
	// 左闭右闭
	int L = 0, R = -1;
	for (int i = 0; i < q; i++) {
		Query it = Q[i];
		while (L < it.l) {
			cnt[x[L]]--;
			res -= cnt[z[L]];
			L++;
		}
		while (L > it.l) {
			L--;
			res += cnt[z[L]];
			cnt[x[L]]++;
		}

		while (R < it.r) {
			R++;
			res += cnt[y[R]];
			cnt[x[R]]++;
		}

		while (R > it.r) {
			cnt[x[R]]--;
			res -= cnt[y[R]];
			R--;
		}
		ans[it.idx] = res;
	}

	for (int i = 1; i <= q; i++) {
		cout << ans[i] << '\n';
	}
	return 0;
}