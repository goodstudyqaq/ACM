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

const int maxn = 3e5 + 5;
char s[maxn];

int k;
int son[maxn][2];
int fa[maxn];
void build() {
	int len = strlen(s + 1);
	int now = len - 1;
	queue< int > Q;
	Q.push(len);
	while (!Q.empty()) {
		int x = Q.front();
		Q.pop();
		if (now == 0) break;
		son[x][1] = now--;
		son[x][0] = now--;
		fa[son[x][0]] = x;
		fa[son[x][1]] = x;
		Q.push(son[x][1]);
		Q.push(son[x][0]);
	}
}
int ans[maxn];

void dfs(int u) {
	char c = s[u];
	if (son[u][0] == -1) {
		if (c == '0' || c == '1') {
			ans[u] = 1;
		} else {
			ans[u] = 2;
		}
		return;
	}

	dfs(son[u][0]);
	dfs(son[u][1]);
	if (c == '0') {
		ans[u] = ans[son[u][0]];
	} else if (c == '1') {
		ans[u] = ans[son[u][1]];
	} else {
		ans[u] = ans[son[u][0]] + ans[son[u][1]];
	}
}

void update(int p, char c) {

	if (son[p][0] == -1) {
		if (c == '0' || c == '1') {
			ans[p] = 1;
		} else {
			ans[p] = 2;
		}
	} else {
		if (c == '0') {
			ans[p] = ans[son[p][0]];
		} else if (c == '1') {
			ans[p] = ans[son[p][1]];
		} else {
			ans[p] = ans[son[p][0]] + ans[son[p][1]];
		}
	}
	int father = fa[p];
	if (father == -1) return;
	update(father, s[father]);
}

int main() {
	memset(son, -1, sizeof(son));
	memset(fa, -1, sizeof(fa));
	scanf("%d", &k);
	scanf("%s", s + 1);
	build();
	int len = strlen(s + 1);
	dfs(len);
	int q;
	scanf("%d", &q);
	int p;
	char c;

	while (q--) {
		scanf("%d %c", &p, &c);
		s[p] = c;
		update(p, c);
		// debug(ans[5], ans[6]);
		printf("%d\n", ans[len]);
	}
	return 0;
}