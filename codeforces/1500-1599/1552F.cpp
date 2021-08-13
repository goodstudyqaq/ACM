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

const int maxn = 4e5 + 5;
const int mod = 998244353;

long long sum[maxn];
#define lowbit(x) x & -x

void add(int idx, long long val) {
	while (idx < maxn) {
		(sum[idx] += val) %= mod;
		idx += lowbit(idx);
	}
}

long long query(int idx) {
	long long res = 0;
	while (idx) {
		(res += sum[idx]) %= mod;
		idx -= lowbit(idx);
	}
	return res;
}

void Add(int l, int r, long long val) {
	add(l, val);
	add(r + 1, -val);
}

vector< int > x;

struct Node {
	int x, y, s;
};
int xcnt;

int main() {
#ifdef LOCAL
	freopen("data.in", "r", stdin);
#endif
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n;
	cin >> n;
	vector< Node > V;
	V.resize(n + 1);
	for (int i = 1; i <= n; i++) {
		cin >> V[i].x >> V[i].y >> V[i].s;
		x.emplace_back(V[i].x);
		x.emplace_back(V[i].y);
	}
	x.emplace_back(0);
	x.emplace_back(V[n].x + 1);
	sort(x.begin(), x.end());
	xcnt = unique(x.begin(), x.end()) - x.begin();

	// push [0, V[n].x + 1]
	int l_idx = lower_bound(x.begin(), x.begin() + xcnt, 0) - x.begin() + 1;
	int r_idx = upper_bound(x.begin(), x.begin() + xcnt, V[n].x + 1) - x.begin();
	Add(l_idx, r_idx, 1);
	for (int i = n; i >= 1; i--) {
		// V[i].x
		int idx = upper_bound(x.begin(), x.begin() + xcnt, V[i].x - 1) - x.begin();
		long long val = query(idx);
		int l_idx = lower_bound(x.begin(), x.begin() + xcnt, V[i].y) - x.begin() + 1;
		if (V[i].s == 1) {
			Add(l_idx, idx, val);
		} else {
			Add(l_idx, idx, val - 1);
		}
	}

	for (int i = 0; i < xcnt; i++) {
		debug(i, x[i]);
	}

	long long res = 0;
	for (int i = 0; i < xcnt - 1; i++) {
		int l = x[i];
		if (l >= V[n].x + 1) break;
		int r = x[i + 1];
		int times = query(i + 1);
		debug(l, r, times);
		res = (res + 1LL * (r - l) * times % mod) % mod;
	}
	res = (res + mod) % mod;
	cout << res << endl;
	return 0;
}