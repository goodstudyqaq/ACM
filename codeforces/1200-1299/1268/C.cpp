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

#define lowbit(x) x & -x

const int maxn = 2e5 + 1;
long long sum1[maxn], sum2[maxn];
void add(int idx, int val, long long* sum) {
	while (idx < maxn) {
		sum[idx] += val;
		idx += lowbit(idx);
	}
}

long long query(int idx, long long* sum) {
	long long res = 0;
	while (idx) {
		res += sum[idx];
		idx -= lowbit(idx);
	}
	return res;
}

vector< int > p, a;
int main() {
#ifdef LOCAL
	freopen("data.in", "r", stdin);
#endif
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n;
	cin >> n;
	p.resize(n + 1);
	a.resize(n + 1);
	for (int i = 1; i <= n; i++) {
		cin >> p[i];
		a[p[i]] = i;
	}

	long long res = 0;
	for (int i = 1; i <= n; i++) {
		int idx = a[i];
		add(idx, 1, sum1);
		add(idx, idx, sum2);

		int val = (i + 1) / 2;
		int l = 1, r = n;
		int ans = -1;
		while (l <= r) {
			int mid = l + r >> 1;
			if (query(mid, sum1) >= val) {
				ans = mid;
				r = mid - 1;
			} else {
				l = mid + 1;
			}
		}
		int number = query(ans, sum1);

		long long tmp = 1LL * ans * number - query(ans, sum2) - 1LL * (0 + number - 1) * number / 2;
		tmp += query(n, sum2) - query(ans, sum2) - 1LL * (i - number) * ans - 1LL * (1 + i - number) * (i - number) / 2;
		long long tmp2 = query(n, sum1) - query(idx, sum1);
		// debug(i, ans, tmp, tmp2);
		cout << res + tmp + tmp2 << ' ';
		res += tmp2;
	}
	return 0;
}