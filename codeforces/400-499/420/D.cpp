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

const int maxn = 2e6 + 5;
const int maxm = 1e6 + 1;
#define lowbit(x) x & -x
int sum[maxn];

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

int val[maxn];
bool vis[maxn];
int ans[maxn];

int n, m;
int get_idx(int num) {
	int l = 1, r = maxn - 1;
	int ans = -1;
	while (l <= r) {
		int mid = l + r >> 1;
		if (query(mid) >= num) {
			ans = mid;
			r = mid - 1;
		} else {
			l = mid + 1;
		}
	}
	return ans;
}

int main() {
	freopen("data.in", "r", stdin);
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++) {
		add(i + maxm, 1);
	}
	int x, y;
	int now = maxm;
	while (m--) {
		scanf("%d %d", &x, &y);
		int idx = get_idx(y);

		if (idx <= maxm) {
			if (val[idx] != x) {
				puts("-1");
				return 0;
			}
		} else {
			if (vis[x]) {
				puts("-1");
				return 0;
			} else {
				ans[idx - maxm] = x;
				vis[x] = 1;
			}
		}
		val[now] = x;
		add(idx, -1);
		add(now, 1);
		now--;
	}

	// for (int i = 1; i <= n; i++) {
	// 	debug(i, ans[i]);
	// }

	int j = 1;
	for (int i = 1; i <= n; i++) {
		if (!ans[i]) {
			while (vis[j]) j++;
			ans[i] = j;
			vis[j] = 1;
		}
		printf("%d ", ans[i]);
	}
	puts("");
	return 0;
}