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

const int maxn = 505;
const int maxm = 5005;
const int maxf = 1e5 + 5;
long long dp[maxn][maxm];
int cnt[maxf];
int fav[maxf];
int h[20];
int n, k;
void init() {
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j <= i * k; j++) {
			for (int p = 0; p <= min(j, k); p++) {
				dp[i][j] = max(dp[i][j], dp[i - 1][j - p] + h[p]);
			}
		}
	}
}

int main() {
	// freopen("data.in", "r", stdin);
	scanf("%d %d", &n, &k);
	for (int i = 1; i <= n * k; i++) {
		int c;
		scanf("%d", &c);
		cnt[c]++;
	}
	for (int i = 1; i <= n; i++) {
		int f;
		scanf("%d", &f);
		fav[f]++;
	}
	for (int i = 1; i <= k; i++) {
		scanf("%d", &h[i]);
	}
	init();

	long long ans = 0;
	for (int i = 1; i <= 1e5; i++) {
		if (fav[i]) {
			int ct = cnt[i];
			debug(i, fav[i], ct);
			ans = (ans + dp[fav[i]][min(cnt[i], fav[i] * k)]);
			debug(ans);
		}
	}
	cout << ans << endl;
	return 0;
}