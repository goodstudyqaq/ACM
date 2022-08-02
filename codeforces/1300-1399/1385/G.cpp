/*
一个2*n的矩阵，里面的值大小1到n，能进行的操作是翻转matrix[1][j]和matrix[2][j]的值，最后使得这两行都是1到n的全排列，问最少操作数
*/

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

int n;
const int maxn = 2e5 + 5;
int a[3][maxn];
int cnt[maxn];

int f[maxn * 2];
int t[maxn * 2];
int find(int u) {
	return u == f[u] ? u : f[u] = find(f[u]);
}

int lastx[maxn], lasty[maxn];
bool vis[maxn * 2];
vector< int > chose;

void init() {
	for (int i = 1; i <= n; i++) {
		cnt[i] = 0;
		f[i] = i;
		f[i + n] = i + n;
		t[i] = 0;
		t[i + n] = 1;
		vis[i] = 0;
		vis[i + n] = 0;
		chose.clear();
	}
}
int work() {
	for (int i = 1; i <= n; i++) {
		if (cnt[i] != 2) {
			return -1;
		}
		lastx[i] = -1;
		lasty[i] = -1;
	}

	for (int i = 1; i <= 2; i++) {
		for (int j = 1; j <= n; j++) {
			int val = a[i][j];
			if (lastx[val] == -1) {
				lastx[val] = i;
				lasty[val] = j;
				continue;
			}

			if (lasty[val] == j) continue;
			int tmp1 = find(j);
			int tmp2 = find(j + n);
			int tmp3 = find(lasty[val]);
			int tmp4 = find(lasty[val] + n);

			if (lastx[val] == i) {
				if (tmp1 == tmp3 || tmp2 == tmp4) {
					return -1;
				}
				if (tmp1 != tmp4) {
					f[tmp1] = tmp4;
					t[tmp4] += t[tmp1];
				}
				if (tmp2 != tmp3) {
					f[tmp2] = tmp3;
					t[tmp3] += t[tmp2];
				}
			} else {
				if (tmp1 == tmp4 || tmp2 == tmp3) {
					return -1;
				}
				if (tmp1 != tmp3) {
					f[tmp1] = tmp3;
					t[tmp3] += t[tmp1];
				}
				if (tmp2 != tmp4) {
					f[tmp2] = tmp4;
					t[tmp4] += t[tmp2];
				}
			}
		}
	}
	int ans = 0;
	for (int i = 1; i <= n; i++) {
		int tmp1 = find(i);
		int tmp2 = find(i + n);
		if (!vis[tmp1] && !vis[tmp2]) {
			int val1 = t[tmp1];
			int val2 = t[tmp2];
			if (val1 < val2) {
				vis[tmp1] = 1;
				ans += val1;
			} else {
				ans += val2;
				vis[tmp2] = 1;
				chose.push_back(i);
			}
		} else if (vis[tmp2]) {
			chose.push_back(i);
		}
	}
	return ans;
}

int main() {
	// freopen("data.in", "r", stdin);
	int T;
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		init();
		for (int i = 1; i <= 2; i++)
			for (int j = 1; j <= n; j++) {
				scanf("%d", &a[i][j]);
				cnt[a[i][j]]++;
			}
		int ans = work();
		printf("%d\n", ans);
		for (auto v : chose) {
			printf("%d ", v);
		}
		puts("");
	}
	return 0;
}