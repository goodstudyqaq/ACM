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

typedef pair< long long, long long > pll;
vector< pll > V;
void init() {
	long long L = 1;
	while (L <= 1e18) {
		V.push_back({ L, L * 2 - 1 });
		if (L == 1e18) break;
		L *= 10;
	}
}

double cal(long long l, long long r) {
	long long all = r - l + 1;
	long long sum = 0;
	for (auto it : V) {
		long long tmp1 = max(l, it.first);
		long long tmp2 = min(r, it.second);
		if (tmp1 <= tmp2) {
			debug(tmp1, tmp2);
			sum += tmp2 - tmp1 + 1;
		}
	}
	return 1.0 * sum / (1.0 * all);
}

const int maxn = 1005;
double p[maxn];
double dp[maxn][maxn];

int main() {
	freopen("data.in", "r", stdin);
	init();
	int N;
	scanf("%d", &N);
	long long L, R;
	for (int i = 1; i <= N; i++) {
		scanf("%I64d %I64d", &L, &R);
		p[i] = cal(L, R);
		debug(i, p[i]);
	}

	int K;
	scanf("%d", &K);
	int need;
	if (K == 0) {
		need = 0;
	} else {
		need = (N * K - 1) / 100 + 1;
	}
	dp[0][0] = 1;
	for (int i = 1; i <= N; i++) {
		for (int j = 0; j <= i; j++) {
			if (j == 0) {
				dp[i][j] = dp[i - 1][j] * (1.0 - p[i]);
			} else {
				dp[i][j] = (dp[i - 1][j] * (1.0 - p[i]) + dp[i - 1][j - 1] * p[i]);
			}
		}
	}

	double ans = 0;
	for (int i = need; i <= N; i++) {
		ans += dp[N][i];
	}
	printf("%.9f\n", ans);
}