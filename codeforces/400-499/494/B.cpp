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

const int maxn = 1e5 + 5;
const int mod = 1e9 + 7;
char s1[maxn], s2[maxn];
int nxt[maxn];

void kmp_pre(char x[], int m, int next[]) {
	int i, j;
	j = next[0] = -1;
	i = 0;
	while (i < m) {
		while (j != -1 && x[i] != x[j]) j = next[j];
		next[++i] = ++j;
	}
}
int s1_len, s2_len;
bool vis[maxn];

void work() {
	int i, j;
	i = j = 0;
	while (i < s1_len) {
		while (j != -1 && s1[i] != s2[j]) j = nxt[j];
		i++, j++;
		if (j >= s2_len) {
			vis[i - s2_len] = 1;
		}
	}
	for (int i = 0; i < s1_len; i++) {
		debug(i, vis[i]);
	}
}
long long dp[maxn];
long long sum[maxn], sum2[maxn];
int lxt_ok[maxn];

int main() {
	freopen("data.in", "r", stdin);
	scanf("%s %s", s1, s2);
	s1_len = strlen(s1);
	s2_len = strlen(s2);
	kmp_pre(s2, s2_len, nxt);
	work();
	memset(lxt_ok, -1, sizeof(lxt_ok));
	for (int i = 0; i < s1_len; i++) {
		if (i != 0) {
			lxt_ok[i] = lxt_ok[i - 1];
		}
		if (vis[i]) {
			lxt_ok[i] = i;
		}
	}
	long long ans = 0;

	for (int i = s2_len - 1; i < s1_len; i++) {
		int tmp = lxt_ok[i - s2_len + 1];
		if (tmp == -1) continue;
		if (tmp != 0)
			dp[i] = sum2[tmp - 1];
		dp[i] = (dp[i] + tmp + 1) % mod;
		sum[i] = (sum[i - 1] + dp[i]) % mod;
		sum2[i] = (sum2[i - 1] + sum[i]) % mod;
		debug(i, dp[i]);
		ans = (ans + dp[i]) % mod;
	}
	printf("%lld\n", ans);
	return 0;
}