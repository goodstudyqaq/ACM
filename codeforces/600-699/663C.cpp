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

const int maxn = 1e5 + 5;
typedef pair< int, int > pii;
vector< pii > V[maxn];
int color[maxn];
vector< int > num[3];

bool dfs(int u, int c, int flag) {
	color[u] = c;
	num[c].push_back(u);

	for (auto e : V[u]) {
		int v = e.first;
		int f = e.second;
		if (color[v] != -1) {
			if ((f ^ flag) == 0 && color[u] != color[v]) {
				return false;
			} else if ((f ^ flag) == 1 && color[u] == color[v]) {
				return false;
			}
		} else {
			if ((f ^ flag) == 0) {
				bool check = dfs(v, c, flag);
				if (!check) return false;
			} else {
				bool check = dfs(v, c ^ 1, flag);
				if (!check) return false;
			}
		}
	}
	return true;
}

int n, m;
vector< int > work(int flag) {
	vector< int > ans;
	memset(color, -1, sizeof(color));
	for (int i = 1; i <= n; i++) {
		if (color[i] == -1) {
			num[0].clear();
			num[1].clear();

			bool f = dfs(i, 0, flag);
			if (!f) {
				for (int i = 1; i <= n + 1; i++) {
					ans.push_back(1);
				}
				return ans;
			}

			int chose = 0;
			if (num[0].size() > num[1].size()) {
				chose = 1;
			}

			for (int j = 0; j < num[chose].size(); j++) {
				ans.push_back(num[chose][j]);
			}
		}
	}
	return ans;
}

int main() {
	freopen("data.in", "r", stdin);
	scanf("%d %d", &n, &m);
	int u, v;
	char s;

	for (int i = 1; i <= m; i++) {
		scanf("%d %d %c", &u, &v, &s);
		int flag = (s == 'B');
		V[u].push_back({ v, flag });
		V[v].push_back({ u, flag });
	}
	vector< int > ans = work(0);
	vector< int > ans2 = work(1);
	if (ans.size() > n && ans2.size() > n) {
		puts("-1");
		return 0;
	}

	if (ans.size() > ans2.size()) {
		swap(ans, ans2);
	}

	cout << ans.size() << endl;
	for (auto v : ans) {
		printf("%d ", v);
	}
	puts("");
	return 0;
}