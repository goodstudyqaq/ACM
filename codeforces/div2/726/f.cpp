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
long long v[maxn], t[maxn];

vector< int > V[maxn];
int color[maxn];

bool dfs(int u, int pre, int f) {
	debug(u, pre, f);
	color[u] = f;
	for (auto to : V[u]) {
		if (color[to]) {
			if (color[to] != 3 - f) {
				return false;
			}
		} else {
			bool flag = dfs(to, u, 3 - f);
			if (!flag) {
				return false;
			}
		}
	}
	return true;
}

int n, m;
void init() {
	for (int i = 1; i <= n; i++) {
		V[i].clear();
		color[i] = 0;
	}
}

int main() {
	// debug(-3 % 2);
	freopen("data.in", "r", stdin);
	int T;
	scanf("%d", &T);
	while (T--) {
		scanf("%d %d", &n, &m);
		init();
		long long vsum = 0, tsum = 0;
		for (int i = 1; i <= n; i++) {
			scanf("%lld", &v[i]);
			vsum += v[i];
		}
		for (int i = 1; i <= n; i++) {
			scanf("%lld", &t[i]);
			tsum += t[i];
		}
		vsum = ((vsum % 2) + 2) % 2;
		tsum = ((tsum % 2) + 2) % 2;
		debug(vsum, tsum);

		for (int i = 1; i <= m; i++) {
			int u, v;
			scanf("%d %d", &u, &v);
			V[u].push_back(v);
			V[v].push_back(u);
		}
		if (vsum ^ tsum) {
			puts("NO");
			continue;
		}
		bool f = dfs(1, -1, 1);
		debug(f);
		if (!f) {
			puts("YES");
			continue;
		}

		long long a = 0, b = 0;
		for (int i = 1; i <= n; i++) {
			if (color[i] == 1) {
				a += t[i] - v[i];
			} else {
				b += t[i] - v[i];
			}
		}
		if (a == b) {
			puts("YES");
		} else {
			puts("NO");
		}
	}
}