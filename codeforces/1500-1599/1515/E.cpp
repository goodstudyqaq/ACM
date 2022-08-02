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

int main() {
#ifdef LOCAL
	freopen("data.in", "r", stdin);
#endif
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n, M;
	cin >> n >> M;
	vector< vector< long long > > C(n + 1, vector< long long >(n + 1, 0));
	C[0][0] = 1;
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j <= n; j++) {
			C[i][j] = C[i - 1][j];
			if (j > 0) {
				C[i][j] = (C[i][j] + C[i - 1][j - 1]) % M;
			}
		}
	}

	vector< long long > two(n + 1, 0);

	two[0] = 1;
	for (int i = 1; i <= n; i++) {
		two[i] = two[i - 1] * 2 % M;
	}

	vector< vector< long long > > dp(n + 2, vector< long long >(n + 2, 0));
	dp[0][0] = 1;
	for (int i = 0; i <= n + 1; i++) {
		for (int j = 0; j <= i; j++) {
			if (dp[i][j] == 0) continue;
			// debug(i, j, dp[i][j]);

			for (int k = 1; i + k + 1 <= n + 1; k++) {
				dp[i + k + 1][j + k] = (dp[i + k + 1][j + k] + dp[i][j] * two[k - 1] % M * C[j + k][k] % M) % M;
			}
		}
	}
	long long res = 0;
	for (int i = 0; i <= n + 1; i++) {
		res = (res + dp[n + 1][i]) % M;
	}
	cout << res << endl;
	return 0;
}