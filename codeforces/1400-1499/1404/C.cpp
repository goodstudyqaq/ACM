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

typedef pair< int, int > pii;
const int maxn = 3e5 + 1;
int sum[maxn];
#define lowbit(x) x & -x

void add(int idx, int val) {
	while (idx < maxn) {
		sum[idx] += val;
		idx += lowbit(idx);
	}
}

int query(int idx) {
	int res = 0;
	while (idx) {
		res += sum[idx];
		idx -= lowbit(idx);
	}
	return res;
}

int main() {
#ifdef LOCAL
	freopen("data.in", "r", stdin);
#endif
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n, q;
	cin >> n >> q;
	vector< int > a(n + 1);
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		a[i] = i - a[i];
		if (a[i] < 0) {
			a[i] = n + 1;
		}
	}

	vector< vector< pii > > queries;
	queries.resize(n + 1);

	for (int i = 1; i <= q; i++) {
		int l, r;
		cin >> l >> r;
		l++;
		r = n - r;
		queries[r].push_back({ i, l });
	}

	vector< int > res(q + 1);
	for (int i = 1; i <= n; i++) {
		int l = 1, r = i;
		int ans = -1;
		while (l <= r) {
			int mid = l + r >> 1;
			int tmp = query(mid);
			if (tmp >= a[i]) {
				ans = mid;
				l = mid + 1;
			} else {
				r = mid - 1;
			}
		}
		if (ans != -1) {
			add(1, 1);
			add(ans + 1, -1);
		}

		for (auto j : queries[i]) {
			int idx = j.first;
			int left = j.second;
			res[idx] = query(left);
		}
	}

	for (int i = 1; i <= q; i++) {
		cout << res[i] << '\n';
	}
	return 0;
}