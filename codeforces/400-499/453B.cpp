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

const int maxn = 105;
//时间复杂度O(nloglogn)
bool is[maxn];
int prm[maxn], id;
void init() {
	memset(is, 1, sizeof(is));
	is[0] = is[1] = 0;
	int k = 0;
	prm[k++] = 2;
	for (int i = 4; i < maxn; i += 2) is[i] = 0;
	int e = ( int )sqrt(0.0 + maxn) + 1;
	int i;
	for (i = 3; i < e; i += 2)
		if (is[i]) {
			prm[k++] = i;
			for (int s = 2 * i, j = i * i; j < maxn; j += s)
				is[j] = 0;
		}
	for (; i < maxn; i += 2)
		if (is[i]) prm[k++] = i;
	id = k;
}

const int mx = 17;
const int maxm = (1 << mx);
const int inf = 0x3f3f3f3f;

int dp[maxn][maxm + 10];

int a[maxn];

int get_status(int val) {
	int res = 0;
	for (int i = mx - 1; i >= 0; i--) {
		int tmp = 0;
		if (val % prm[i] == 0) {
			tmp = 1;
		}
		res = res * 2 + tmp;
	}
	return res;
}

bool check(int s1, int s2) {
	for (int i = 0; i < mx; i++) {
		if ((s2 >> i) & 1) {
			if (((s1 >> i) & 1) == 0) {
				return false;
			}
		}
	}
	return true;
}

typedef pair< int, int > pii;
pii work(int val1, int val2) {
	int res = abs(val2 - val1);
	int chose = val1;
	return { res, chose };
}

pii use[maxn][maxm + 10];
int skk[70];
vector< int > V[maxm];
vector< int > V2;
int main() {
	freopen("data.in", "r", stdin);
	init();
	int n;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
	}
	memset(dp, inf, sizeof(dp));
	dp[0][0] = 0;

	for (int i = 2; i < 60; i++) {
		int si = get_status(i);
		skk[i] = si;
	}
	V2.push_back(0);
	int aaaa = 0;
	for (int i = 0; i < maxm; i++) {
		for (int j = 2; j < 60; j++) {
			int sj = skk[j];
			if (check(i, sj)) {
				V[i].push_back(j);
			}
		}
		if (V[i].size()) {
			V2.push_back(i);
			aaaa += V[i].size();
		}
	}
	debug(V2.size());
	debug(aaaa);

	for (int i = 1; i <= n; i++) {
		for (auto j : V2) {
			if (dp[i - 1][j] != inf) {
				dp[i][j] = dp[i - 1][j] + abs(1 - a[i]);
				use[i][j] = { -1, 1 };
			}
			for (auto k : V[j]) {
				int sk = skk[k];
				if (dp[i - 1][j ^ sk] == inf) continue;
				pii it = work(k, a[i]);
				if (dp[i][j] > dp[i - 1][j ^ sk] + it.first) {
					dp[i][j] = dp[i - 1][j ^ sk] + it.first;
					use[i][j] = { sk, it.second };
				}
			}
		}
	}

	int res = 1e9;
	int chose = -1;
	for (int i = 0; i < maxm; i++) {
		if (dp[n][i] != inf && res > dp[n][i]) {
			res = dp[n][i];
			chose = i;
		}
	}
	debug(chose);
	int now_idx = n, now_status = chose;
	while (now_idx >= 1) {
		auto it = use[now_idx][now_status];
		a[now_idx] = it.second;
		if (it.first != -1) {
			now_status = now_status ^ it.first;
		}
		now_idx--;
	}
	for (int i = 1; i <= n; i++) {
		printf("%d ", a[i]);
	}
	puts("");
	return 0;
}