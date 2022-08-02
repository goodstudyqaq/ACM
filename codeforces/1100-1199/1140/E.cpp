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

long long quick(long long a, long long b) {
	long long res = 1;
	while (b) {
		if (b % 2) res = res * a % mod;
		b /= 2;
		a = a * a % mod;
	}
	return res;
}

int n, k;

bool check(vector< int >& a) {
	for (int i = 0; i < a.size(); i++) {
		if (a[i] != -1) return false;
	}
	return true;
}

bool check2(vector< int >& a) {
	for (int i = 0; i < a.size() - 1; i++) {
		if (a[i] != -1 && a[i] == a[i + 1]) return true;
	}
	return false;
}

vector< vector< long long > > dp;
long long work2(int val1, int val2, int num) {
	if (val1 == val2) {
		return dp[num][1];
	} else {
		return dp[num][0];
	}
}

long long work(vector< int >& a) {

	int sz = a.size();
	if (check(a)) {
		return quick(k - 1, sz - 1) * k % mod;
	}

	if (check2(a)) {
		return 0;
	}
	int beg = 0;
	long long res = 1;
	while (beg < sz && a[beg] == -1) {
		res = res * (k - 1) % mod;
		beg++;
	}
	int ed = sz - 1;
	while (ed >= 0 && a[ed] == -1) {
		res = res * (k - 1) % mod;
		ed--;
	}

	while (beg < ed) {
		int go = beg;
		while (go < ed && a[go] != -1) {
			go++;
		}
		int val1 = a[go - 1];
		int go2 = go;
		while (go2 < ed && a[go2] == -1) {
			go2++;
		}
		int val2 = a[go2];
		res = res * work2(val1, val2, go2 - go) % mod;
		beg = go2;
	}
	return res;
}

int main() {
#ifdef LOCAL
	freopen("data.in", "r", stdin);
#endif
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n >> k;
	dp.resize(n + 1, vector< long long >(2, 0));

	dp[0][0] = 1;
	dp[0][1] = 0;

	for (int i = 1; i <= n; i++) {
		dp[i][0] = (dp[i - 1][1] + dp[i - 1][0] * (k - 2) % mod) % mod;
		dp[i][1] = dp[i - 1][0] * (k - 1) % mod;
		debug(i, dp[i][0], dp[i][1]);
	}

	vector< int > a[2];
	for (int i = 1; i <= n; i++) {
		int val;
		cin >> val;
		a[i % 2].emplace_back(val);
	}

	long long res = work(a[0]) * work(a[1]) % mod;
	cout << res << endl;
	return 0;
}