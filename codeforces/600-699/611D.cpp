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

const int maxn = 5005;
const int mod = 1e9 + 7;

//SA[i]=a 排名为i的下标为a
//rank[a]=i 下标为a的排名为i
//height[i]=a 排名为i的和排名为i-1是最长公共前缀
//下标从1到N 千万不能搞错
#define rank rk
int ch[maxn];
int cntA[maxn], cntB[maxn], A[maxn], B[maxn], tsa[maxn], SA[maxn], rank[maxn], height[maxn];
int N;
void get_SA() {
	for (int i = 0; i <= 200; i++) cntA[i] = 0;
	for (int i = 1; i <= N; i++) cntA[ch[i]]++;
	for (int i = 1; i <= 200; i++) cntA[i] += cntA[i - 1];
	for (int i = N; i >= 1; i--) SA[cntA[ch[i]]--] = i;
	rank[SA[1]] = 1;
	for (int i = 2; i <= N; i++) {
		rank[SA[i]] = rank[SA[i - 1]];
		if (ch[SA[i]] != ch[SA[i - 1]])
			rank[SA[i]]++;
	}
	for (int step = 1; rank[SA[N]] < N; step <<= 1) {
		for (int i = 1; i <= N; i++) cntA[i] = cntB[i] = 0;
		for (int i = 1; i <= N; i++) {
			cntA[A[i] = rank[i]]++;
			cntB[B[i] = (i + step <= N) ? rank[i + step] : 0]++;
		}
		for (int i = 1; i <= N; i++) cntA[i] += cntA[i - 1], cntB[i] += cntB[i - 1];
		for (int i = N; i >= 1; i--) tsa[cntB[B[i]]--] = i;
		for (int i = N; i >= 1; i--) SA[cntA[A[tsa[i]]]--] = tsa[i];
		rank[SA[1]] = 1;
		for (int i = 2; i <= N; i++) {
			rank[SA[i]] = rank[SA[i - 1]];
			if (A[SA[i]] != A[SA[i - 1]] || B[SA[i]] != B[SA[i - 1]])
				rank[SA[i]]++;
		}
	}
}
void get_Height() {
	int i, j, k = 0;
	for (int i = 1; i <= N; i++) {
		if (k) k--;
		j = SA[rank[i] - 1];
		while (ch[i + k] == ch[j + k]) k++;
		height[rank[i]] = k;
	}
}

long long dp[maxn][maxn];
long long sum[maxn][maxn];
char s[maxn];

int Height[maxn][20];
void rmq() {
	unor
	for (int i = 1; i <= N; i++) {
		Height[i][0] = height[i];
	}

	for (int j = 1; j < 20; j++) {
		for (int i = 1; i <= N; i++) {
			int go = i + (1 << j) - 1;
			if (go > N) continue;
			Height[i][j] = min(Height[i][j - 1], Height[i + (1 << (j - 1))][j - 1]);
		}
	}
}

int query(int a, int b) {
	a++;
	int k = log2(b - a + 1);
	return min(Height[a][k], Height[b - (1 << k) + 1][k]);
}

int main() {
	freopen("data.in", "r", stdin);
	scanf("%d", &N);
	scanf("%s", s);
	for (int i = 0; i < N; i++) {
		ch[i + 1] = s[i] - '0';
	}
	get_SA();
	get_Height();
	rmq();

	dp[0][0] = 1;
	sum[0][0] = 1;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= i; j++) {
			if (s[j - 1] == '0') {
				dp[i][j] = 0;
			} else {
				int len = i - j + 1;
				int left = j - 1;
				int right = left - len + 1;
				bool flag = true;
				if (right >= 1) {
					int r1 = rank[right];
					int r2 = rank[j];
					int tmp = query(min(r1, r2), max(r1, r2));
					if (tmp >= len) {
						flag = false;
					} else {
						char s1 = s[right + tmp - 1];
						char s2 = s[j + tmp - 1];
						if (s1 > s2) {
							flag = false;
						}
					}
					// debug(i, j, flag, tmp);
					if (flag) {
						dp[i][j] = (((dp[i][j] + sum[left][left]) % mod - sum[left][right - 1]) % mod + mod) % mod;
					} else {
						dp[i][j] = (((dp[i][j] + sum[left][left]) % mod - sum[left][right]) % mod + mod) % mod;
					}
				} else {
					dp[i][j] = (dp[i][j] + sum[left][left]) % mod;
				}
			}

			sum[i][j] = (sum[i][j - 1] + dp[i][j]) % mod;
			debug(i, j, dp[i][j], sum[i][j]);
		}
	}
	printf("%lld\n", sum[N][N]);
	return 0;
}