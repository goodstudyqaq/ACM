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

const int maxn = 1e6 + 5;
int a[maxn];
int b[maxn];
bool vis[maxn];

#define lowbit(x) x & -x
int sum1[maxn], sum2[maxn];
void add(int idx, int val, int* sum) {
	while (idx < maxn) {
		sum[idx] += val;
		idx += lowbit(idx);
	}
}

int query(int idx, int* sum) {
	int res = 0;
	while (idx) {
		res += sum[idx];
		idx -= lowbit(idx);
	}
	return res;
}

int idx[maxn];

typedef pair< int, int > pii;
int n, k;

int check(int l, int r) {
	return query(r, sum1) - query(l - 1, sum1);
}

pii get_range(int the_idx) {
	pii range;
	int l = 1, r = the_idx;
	int ans = -1;
	while (l <= r) {
		int mid = l + r >> 1;
		if (check(mid, the_idx) == 0) {
			ans = mid;
			r = mid - 1;
		} else {
			l = mid + 1;
		}
	}
	range.first = ans;
	l = the_idx, r = n;
	ans = -1;
	while (l <= r) {
		int mid = l + r >> 1;
		if (check(the_idx, mid) == 0) {
			ans = mid;
			l = mid + 1;
		} else {
			r = mid - 1;
		}
	}
	range.second = ans;
	return range;
}
int main() {
	freopen("data.in", "r", stdin);
	scanf("%d %d", &n, &k);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
		idx[a[i]] = i;
	}
	for (int i = 1; i <= k; i++) {
		scanf("%d", &b[i]);
		vis[b[i]] = 1;
	}

	if (n == k) {
		puts("0");
		return 0;
	}

	int del_num = 0;
	long long ans = 0;
	for (int i = 1; i <= n; i++) {
		if (vis[i]) {
			add(idx[i], 1, sum1);
			continue;
		} else {
			int the_idx = idx[i];
			pii range = get_range(the_idx);
			debug(i, range.first, range.second);
			ans += range.second - range.first + 1 - (query(range.second, sum2) - query(range.first - 1, sum2));
			add(the_idx, 1, sum2);
		}
	}
	cout << ans << endl;
}