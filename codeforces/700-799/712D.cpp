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

const int mod = 1e9 + 7;
int main() {
#ifdef LOCAL
	freopen("data.in", "r", stdin);
#endif
	ios::sync_with_stdio(false);
	cin.tie(0);
	int a, b, k, t;
	cin >> a >> b >> k >> t;

	vector< vector< long long > > dp;
	dp.resize(2, vector< long long >(k * t * 2 + 1, 0));

	int f = 0;
	dp[f][0] = 1;

	vector< long long > sum(k * t * 2 + 1, 0);
	for (int i = 1; i <= t; i++) {
		for (int j = 0; j <= k * t * 2; j++) {
			if (j == 0) {
				sum[j] = dp[f][j];
				continue;
			}
			sum[j] = (sum[j - 1] + dp[f][j]) % mod;
		}
		int new_f = f ^ 1;
		for (int j = 0; j <= k * t * 2; j++) {
			int small = max(0, j - 2 * k);
			if (small == 0) {
				dp[new_f][j] = sum[j];
			} else {
				dp[new_f][j] = ((sum[j] - sum[small - 1]) % mod + mod) % mod;
			}
		}
		f = new_f;
	}

	for (int i = 0; i <= k * t * 2; i++) {
		if (i == 0) {
			sum[i] = dp[f][0];
		} else {
			sum[i] = (sum[i - 1] + dp[f][i]) % mod;
		}
	}

	long long res = 0;
	for (int i = 0; i <= k * t * 2; i++) {
		int small = max(i + b - a + 1, 0);
		if (small <= k * t * 2) {
			long long tmp;
			if (small == 0) {
				tmp = sum[k * t * 2];
			} else {
				tmp = ((sum[k * t * 2] - sum[small - 1]) % mod + mod) % mod;
			}
			res = (res + dp[f][i] * tmp % mod) % mod;
		}
	}
	cout << res << endl;
	return 0;
}