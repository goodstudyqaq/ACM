/*
 一个n边形给出切割后的n-2个三角形的下标，求这个n边形的下标顺序，以及切三角形的顺序
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

const int maxn = 1e5 + 5;
int a[maxn][5];
int in[maxn];
typedef pair< int, int > pii;
typedef pair< pii, int > piii;
set< piii > S[maxn];
vector< int > V[maxn];

vector< int > ans;
bool vis[maxn];

void dfs(int u, int pre) {
	printf("%d ", u);
	vis[u] = 1;
	for (auto v : V[u]) {
		if (v == pre) continue;
		if (vis[v]) continue;
		dfs(v, u);
	}
}
int f[maxn];
int find(int u) {
	return u == f[u] ? u : f[u] = find(f[u]);
}

int main() {
	freopen("data.in", "r", stdin);
	int T;
	scanf("%d", &T);
	while (T--) {
		int n;
		scanf("%d", &n);

		for (int i = 1; i <= n; i++) {
			in[i] = 0;
			S[i].clear();
			V[i].clear();
			ans.clear();
			vis[i] = 0;
			f[i] = i;
		}

		for (int i = 1; i <= n - 2; i++) {
			scanf("%d %d %d", &a[i][1], &a[i][2], &a[i][3]);
			sort(a[i] + 1, a[i] + 4);
			in[a[i][1]]++;
			in[a[i][2]]++;
			in[a[i][3]]++;
			S[a[i][1]].insert({ { a[i][2], a[i][3] }, i });
			S[a[i][2]].insert({ { a[i][1], a[i][3] }, i });
			S[a[i][3]].insert({ { a[i][1], a[i][2] }, i });
		}

		if (n == 3) {
			cout << a[1][1] << ' ' << a[1][2] << ' ' << a[1][3] << endl;
			cout << 1 << endl;
			continue;
		}

		queue< int > Q;
		for (int i = 1; i <= n; i++) {
			if (in[i] == 1) {
				Q.push(i);
			}
		}
		while (!Q.empty()) {
			int x = Q.front();
			Q.pop();
			if (S[x].empty()) continue;
			auto it = *S[x].begin();

			debug(x, it, it.second);
			ans.push_back(it.second);

			int fx = find(x);
			int fff = find(it.first.first);
			int ffs = find(it.first.second);

			if (fx != fff) {
				debug(x, it.first.first);
				V[x].push_back(it.first.first);
				V[it.first.first].push_back(x);
				f[fff] = fx;
			}
			if (fx != ffs) {
				debug(x, it.first.second);
				V[x].push_back(it.first.second);
				V[it.first.second].push_back(x);
				f[ffs] = fx;
			}

			in[it.first.first]--;
			if (in[it.first.first] == 1) {
				Q.push(it.first.first);
			}
			in[it.first.second]--;
			if (in[it.first.second] == 1) {
				Q.push(it.first.second);
			}
			S[it.first.first].erase({ { x, it.first.second }, it.second });
			S[it.first.first].erase({ { it.first.second, x }, it.second });
			S[it.first.second].erase({ { x, it.first.first }, it.second });
			S[it.first.second].erase({ { it.first.first, x }, it.second });
		}

		vector< int > tmp;
		for (int i = 1; i <= n; i++) {
			if (V[i].size() < 2) {
				tmp.push_back(i);
			}
		}
		if (tmp.size() == 2) {
			V[tmp[0]].push_back(tmp[1]);
			V[tmp[1]].push_back(tmp[0]);
		}

		dfs(1, -1);
		puts("");
		for (auto it : ans) {
			printf("%d ", it);
		}
		puts("");
	}
}