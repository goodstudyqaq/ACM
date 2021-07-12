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
const int maxn = 2000 + 10;
const int maxm = 1e5 + 5;
const int mod = 1e9 + 7;
long long dp[maxn][maxn];
char s[maxm];
void init() {
	dp[0][0] = 1;
	for (int i = 1; i < maxn; i++) {
		for (int j = 0; j <= i; j++) {
			if (j - 1 >= 0) {
				dp[i][j] = (dp[i][j] + dp[i - 1][j - 1]) % mod;
			}
			dp[i][j] = (dp[i][j] + dp[i - 1][j + 1]) % mod;
		}
	}
}


int main() {
	freopen("data.in", "r", stdin);
	int n, m;
	scanf("%d %d", &n, &m);
	scanf("%s", s + 1);
	if (n % 2) {
		puts("0");return 0;
	}


	init();
	int mi = 0, mx = 0;
	int now = 0;
	for (int i = 1; i <= m; i++) {
		int flag = 1;
		if (s[i] == ')') flag = -1;
		now = now + flag;
		mi = min(mi, now);
		mx = max(0, mx + flag);
	}

	if (n == m) {
		if (mi == 0 && mx == 0) {
			puts("1");
		} else {
			puts("0");
		}
		return 0;
	}
	if (mi > 2000 || mx > 2000) {
		puts("0");
		return 0;
	}

	mi = abs(mi);
	int k = n - m;

	long long ans = 0;
	for (int i = mi; i <= k - mx; i++) {
		for (int j = mi; j <= i; j++) {
			int tmp = j - mi + mx;
			if (tmp > maxn) break;
			ans = (ans + dp[i][j] * dp[k - i][tmp] % mod) % mod;
		}
	}
	cout << ans << endl;
}