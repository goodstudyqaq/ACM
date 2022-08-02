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

const int maxn = 1e6 + 5;
vector< int > V[maxn];

int fa[maxn][30];
void dfs(int u, int pre) {
	fa[u][0] = pre;
	for (auto v : V[u]) {
		if (v == pre) continue;
		dfs(v, u);
	}
}

void rmq(int n) {
	for (int i = 1; i < 30; i++) {
		for (int j = 1; j <= n; j++) {
			int to = fa[j][i - 1];
			if (to == -1) {
				fa[j][i] = -1;
				continue;
			}
			fa[j][i] = fa[to][i - 1];
		}
	}
}
int flag[maxn];

int main() {
	freopen("data.in", "r", stdin);
	int n, k;
	scanf("%d %d", &n, &k);
	int u, v;
	for (int i = 1; i < n; i++) {
		scanf("%d %d", &u, &v);
		V[u].push_back(v);
		V[v].push_back(u);
	}
	dfs(n, -1);
	rmq(n);
	flag[n] = 1;
	int now_need = n - k - 1;

	for (int i = n - 1; i >= 1; i--) {
		if (flag[i]) continue;
		int go_num = 1;
		int now = i;
		if (now_need)
			for (int j = 29; j >= 0; j--) {
				if (now == -1) continue;
				if (fa[now][j] == -1) continue;
				if (flag[fa[now][j]]) continue;
				// debug(now, j, fa[now][j]);
				go_num += (1 << j);
				now = fa[now][j];
			}
		if (go_num <= now_need) {
			now_need -= go_num;
			now = i;
			while (flag[now] == 0) {
				flag[now] = 1;
				now = fa[now][0];
			}
		}
	}
	for (int i = 1; i <= n; i++) {
		if (flag[i] == 0) {
			printf("%d ", i);
		}
	}
	return 0;
}