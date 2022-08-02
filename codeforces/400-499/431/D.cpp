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

const int maxn = 65;
long long C[maxn][maxn];
void init() {
	for (int i = 0; i < 65; i++) {
		C[i][0] = 1;
		for (int j = 1; j <= i; j++) {
			C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
			if (C[i][j] > 1e18) { C[i][j] = 1e18; }
		}
	}
}

vector< int > v;

int k;
long long dfs(int d, int val, bool limit) {
	if (d == -1) {
		return val == k;
	}
	int len = d + 1;
	if (len + val < k) {
		return 0;
	}
	if (val > k) {
		return 0;
	}
	if (!limit) {
		return C[len][k - val];
	}
	if (v[d] == 1) {
		long long res = dfs(d - 1, val, false);
		res = res + dfs(d - 1, val + 1, true);
		return res;
	} else {
		return dfs(d - 1, val, true);
	}
}

long long work(long long val) {
	v.clear();
	long long val2 = val * 2;
	while (val) {
		v.push_back(val % 2);
		val /= 2;
	}
	long long res1 = dfs(v.size() - 1, 0, true);
	v.clear();
	while (val2) {
		v.push_back(val2 % 2);
		val2 /= 2;
	}
	long long res2 = dfs(v.size() - 1, 0, true);
	return res2 - res1;
}

int main() {
#ifdef LOCAL
	freopen("data.in", "r", stdin);
#endif
	ios::sync_with_stdio(false);
	cin.tie(0);
	init();
	long long m;
	cin >> m >> k;
	long long l = 1, r = 1e18;
	long long ans = -1;
	while (l <= r) {
		long long mid = l + r >> 1;
		long long val = work(mid);
		if (val == m) {
			cout << mid << endl;
			return 0;
		} else if (val < m) {
			l = mid + 1;
		} else {
			r = mid - 1;
		}
	}
	debug("end");
	return 0;
}