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

vector< vector< int > > to;

vector< int > DFN, LOW, vis;
int id;
vector< int > belong;
int cnt;
vector< int > stk;
int tot1;

void tarjan(int u) {
	DFN[u] = LOW[u] = ++id;
	stk[tot1++] = u;
	vis[u] = 1;

	for (auto v : to[u]) {
		if (!DFN[v]) {
			tarjan(v);
			LOW[u] = min(LOW[u], LOW[v]);
		} else if (vis[v]) {
			LOW[u] = min(LOW[u], DFN[v]);
		}
	}

	if (LOW[u] == DFN[u]) {
		cnt++;
		int v;
		do {
			v = stk[tot1 - 1];
			vis[v] = 0;
			belong[v] = cnt;
			tot1--;
		} while (v != u);
	}
}

unordered_map< int, int > M;

vector< vector< int > > V;
vector< int > in;
typedef pair< int, int > pii;

vector< pii > ans;
int now_u;
vector< int > f;

int find(int u) {
	return u == f[u] ? u : f[u] = find(f[u]);
}

void dfs(int u) {
	// 不可能有环

	if (V[u].size() == 0) {
		ans.push_back({ u, now_u });
	}
	for (auto v : V[u]) {
		dfs(v);
	}
}

int main() {
#ifdef LOCAL
	freopen("data.in", "r", stdin);
#endif
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n;
	cin >> n;

	to.resize(n + 1);
	DFN.resize(n + 1);
	LOW.resize(n + 1);
	vis.resize(n + 1);
	belong.resize(n + 1);
	stk.resize(n + 1);
	V.resize(n + 1);
	in.resize(n + 1);
	f.resize(n + 1);
	for (int i = 1; i <= n; i++) {
		f[i] = i;
	}
	vector< int > in2(n + 1, 0);

	for (int i = 1; i <= n; i++) {
		int v;
		cin >> v;
		to[i].push_back(v);
		int fi = find(i);
		int ft = find(v);
		f[fi] = ft;
		in2[v]++;
	}

	unordered_set< int > S;
	unordered_map< int, int > M2, M3;
	for (int i = 1; i <= n; i++) {
		int fi = find(i);
		S.insert(fi);
		if (to[i].size() == 0) {
			M2[fi] = i;
		}
		if (in2[i] == 0) {
			M3[fi] = i;
		}
	}

	if (S.size() > 1) {
		int lst = -1;
		int beg = -1;

		for (auto it : S) {
			if (lst == -1) {
				beg = lst = it;
				continue;
			}
			int lst_idx = lst;
			if (M2.count(lst)) {
				lst_idx = M2[lst];
			}
			int it_idx = it;
			if (M3.count(it)) {
				it_idx = M3[it];
			}
			ans.push_back({ lst_idx, it_idx });
			to[lst_idx].push_back(it_idx);
			lst = it;
		}

		int lst_idx = lst;
		if (M2.count(lst)) {
			lst_idx = M2[lst];
		}
		int it_idx = beg;
		if (M3.count(beg)) {
			it_idx = M3[beg];
		}

		ans.push_back({ lst_idx, it_idx });
		to[lst_idx].push_back(it_idx);
	}

	for (int i = 1; i <= n; i++) {
		if (!DFN[i]) {
			id = 0;
			tarjan(i);
		}
	}

	for (int i = 1; i <= n; i++) {
		M[belong[i]] = i;
	}

	// 缩点
	for (int i = 1; i <= n; i++) {
		for (auto v : to[i]) {
			int bi = belong[i];
			int bv = belong[v];
			if (bi != bv) {
				debug(i, v, bi, bv);
				V[M[bi]].push_back(M[bv]);
				in[M[bv]]++;
			}
		}
	}

	// 拿 in[u] = 0 的点去连边
	for (int i = 1; i <= n; i++) {
		if (V[i].size() && in[i] == 0) {
			now_u = i;
			dfs(i);
		}
	}

	cout << ans.size() << '\n';
	for (auto it : ans) {
		cout << it.first << ' ' << it.second << '\n';
	}

	return 0;
}