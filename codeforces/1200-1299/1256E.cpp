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

const int maxn = 2e5 + 5;
typedef pair< int, int > pii;
pii a[maxn];

int n;
long long dp[maxn];
int chose_idx[maxn];
int ans[maxn];
int main() {
	freopen("data.in", "r", stdin);
	scanf("%d", &n);
	int k = 3;

	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i].first);
		a[i].second = i;
	}
	sort(a + 1, a + 1 + n);
	for (int i = 1; i <= n; i++) {
		dp[i] = 3e14;
	}
	dp[3] = -a[1].first + a[3].first;
	dp[0] = 0;
	long long mi = dp[0] - a[1].first;
	int idx = 1;
	for (int i = 4; i <= n; i++) {
		if (mi > dp[i - k] - a[i - k + 1].first) {
			mi = dp[i - k] - a[i - k + 1].first;
			idx = i - k + 1;
		}
		dp[i] = a[i].first + mi;
		chose_idx[i] = idx;
	}

	int now = n;
	int ncnt = 0;
	while (now >= 1) {
		ncnt++;
		int go = chose_idx[now];
		for (int i = go; i <= now; i++) {
			ans[a[i].second] = ncnt;
		}
		now = go - 1;
	}

	printf("%lld %d\n", dp[n], ncnt);
	for (int i = 1; i <= n; i++) {
		printf("%d ", ans[i]);
	}
	puts("");
	return 0;
}