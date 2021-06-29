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

const int maxn = 3005;
int a[maxn];
int mx[maxn];
bool vis[maxn][maxn];

int n, k;
int res;
void dfs(int x, int y, int d) {
	if (vis[x][y]) return;
	vis[x][y] = 1;
	res++;
	if (d == k || y >= n + 1) {
		return;
	}

	// if (a[x]) {
	// 	if (mx[y]) dfs(y + 1, y + 2, d + 1);
	// 	if (mx[y] != 100) dfs(x, y + 1, d + 1);
	// }
	// if (a[x] != 100 && mx[y]) dfs(y, y + 1, d + 1);

	if (a[x] && mx[y] != 0) {
		dfs(y + 1, y + 2, d + 1);
	}
	if (mx[y] != 100 && a[x]) {
		dfs(x, y + 1, d + 1);
	}
	if (mx[y] != 0 && a[x] != 100) {
		dfs(y, y + 1, d + 1);
	}
}

int main() {
	freopen("data.in", "r", stdin);
	scanf("%d %d", &n, &k);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
	}

	for (int i = n; i >= 1; i--) {
		mx[i] = max(mx[i + 1], a[i]);
	}

	dfs(1, 2, 0);
	cout << res << endl;
}