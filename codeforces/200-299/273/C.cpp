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
vector< int > V[maxn];
int color[maxn];
int enemies[maxn];

bool change(int u, bool flag, int val) {
	int res = 0;

	for (auto v : V[u]) {
		if (color[v] == flag) {
			res++;
		}
	}
	if (res >= 2) {
		return false;
	}
	if (val == 1) {
		enemies[u] = res;
	}
	for (auto v : V[u]) {
		if (color[v] == flag) {
			enemies[v] += val;
		}
	}
	return true;
}

bool dfs(int u, bool flag) {
	for (auto v : V[u]) {
		if (color[v] == flag && enemies[v] > 1) {
			return false;
		}
	}

	for (auto v : V[u]) {
		if (color[v] != -1) {
			continue;
		} else {
			bool result = false;
			if (change(v, flag ^ 1, 1)) {
				color[v] = flag ^ 1;
				if (dfs(v, flag ^ 1)) {
					result = true;
				}
				if (!result)
					change(v, flag ^ 1, -1);
			}
			if (!result && change(v, flag, 1)) {
				color[v] = flag;
				result |= dfs(v, flag);
			}
			if (!result) {
				enemies[v] = 0;
				return false;
			}
		}
	}
	return true;
}

int main() {
	freopen("data.in", "r", stdin);
	int n, m;
	scanf("%d %d", &n, &m);
	int u, v;
	for (int i = 1; i <= m; i++) {
		scanf("%d %d", &u, &v);
		V[u].push_back(v);
		V[v].push_back(u);
	}
	memset(color, -1, sizeof(color));

	for (int i = 1; i <= n; i++) {
		if (color[i] != -1) continue;
		color[i] = 0;
		if (!dfs(i, 0)) {
			puts("-1");
			return 0;
		}
	}
	for (int i = 1; i <= n; i++) {
		printf("%d", color[i]);
	}
	return 0;
}