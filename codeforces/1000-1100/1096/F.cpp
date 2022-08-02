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
const int mod = 998244353;

#define lowbit(x) x & -x
vector< int > sum;
void add(int idx, int val) {
	while (idx < sum.size()) {
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

int quick(int a, int b) {
	int res = 1;
	while (b) {
		if (b % 2) res = 1LL * res * a % mod;
		b /= 2;
		a = 1LL * a * a % mod;
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
	long long res = 0;
	vector< int > p(n + 1);
	vector< int > v2;
	for (int i = 1; i <= n; i++) {
		cin >> p[i];
		if (p[i] != -1) v2.push_back(p[i]);
	}
	sort(v2.begin(), v2.end());

	vector< int > one(n + 1, 0);
	for (int i = 1; i <= n; i++) {
		if (p[i] == -1) {
			one[i]++;
		}
		one[i] += one[i - 1];
	}

	// 两个未知数的贡献
	int inv2 = quick(2, mod - 2);
	int unknown_number = n - v2.size();
	res = (res + 1LL * unknown_number * (unknown_number - 1) % mod * inv2 % mod * inv2 % mod) % mod;
	debug(res);

	// 未知数 + 已知数
	int all_one_inv = quick(one[n], mod - 2);
	for (int i = 1; i <= n; i++) {
		if (p[i] != -1) {
			// 左边未知的位置个数
			int one_cnt = one[i];
			int big = n - p[i];
			int idx = lower_bound(v2.begin(), v2.end(), p[i]) - v2.begin();
			int big2 = v2.size() - idx - 1;
			big -= big2;

			res = (res + 1LL * one_cnt * all_one_inv % mod * big % mod) % mod;
			debug(res);

			// 右边未知的位置个数
			one_cnt = one[n] - one[i];
			int small = p[i] - 1;
			int small2 = idx;
			small -= small2;
			res = (res + 1LL * one_cnt * all_one_inv % mod * small % mod) % mod;
		}
	}
	debug(res);

	// 两个已知数的贡献
	sum.resize(n + 1);
	for (int i = 1; i <= n; i++) {
		if (p[i] != -1) {
			int val = p[i];
			res = ((res + query(n)) % mod - query(val)) % mod;
			add(val, 1);
		}
	}
	res = (res + mod) % mod;
	cout << res << endl;
	return 0;
}