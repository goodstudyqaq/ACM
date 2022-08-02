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

struct node {
	int dep;
	int nxt[2];
};
vector< node > nodes;
int ncnt;
int rt;
int new_node(int dep) {
	node u;
	memset(u.nxt, -1, sizeof(u.nxt));
	u.dep = dep;
	nodes.push_back(u);
	return nodes.size() - 1;
}

void work(int val) {
	vector< int > v;
	// debug(val);
	for (int i = 0; i < 30; i++) {
		v.push_back(val % 2);
		val /= 2;
	}
	// for (int i = v.size() - 1; i >= 0; i--) {
	// 	cout << v[i] << ' ';
	// }
	// cout << endl;
	int now = rt;
	for (int i = v.size() - 1; i >= 0; i--) {
		int go = v[i];
		if (nodes[now].nxt[go] == -1) {
			int tmp = new_node(i);

			nodes[now].nxt[go] = tmp;
		}
		now = nodes[now].nxt[go];
	}
}

long long ans;
typedef pair< int, int > pii;
long long dfs2(int u, int v) {
	// debug(u, v, nodes[u].dep);
	if (nodes[u].dep == 0) return 0;
	long long mx = 1LL << nodes[u].dep;
	bool f = false;
	if (nodes[u].nxt[0] != -1 && nodes[v].nxt[0] != -1) {
		mx = min(mx, dfs2(nodes[u].nxt[0], nodes[v].nxt[0]));
		f = true;
	}
	if (nodes[u].nxt[1] != -1 && nodes[v].nxt[1] != -1) {
		mx = min(mx, dfs2(nodes[u].nxt[1], nodes[v].nxt[1]));
		f = true;
	}
	if (f) return mx;
	if (nodes[u].nxt[0] != -1 && nodes[v].nxt[1] != -1) {
		mx = min(mx, dfs2(nodes[u].nxt[0], nodes[v].nxt[1]) + (1LL << (nodes[u].dep - 1)));
	}
	if (nodes[u].nxt[1] != -1 && nodes[v].nxt[0] != -1) {
		mx = min(mx, dfs2(nodes[u].nxt[1], nodes[v].nxt[0]) + (1LL << (nodes[u].dep - 1)));
	}
	return mx;
}

void dfs(int u) {
	if (nodes[u].nxt[0] != -1 && nodes[u].nxt[1] != -1) {
		// debug(u);
		dfs(nodes[u].nxt[0]);
		dfs(nodes[u].nxt[1]);
		// long long tmp = dfs2(nodes[u].nxt[0], nodes[u].nxt[1]);
		ans += dfs2(nodes[u].nxt[0], nodes[u].nxt[1]) + (1LL << (nodes[u].dep - 1));
	} else if (nodes[u].nxt[0] != -1) {
		dfs(nodes[u].nxt[0]);
	} else if (nodes[u].nxt[1] != -1) {
		dfs(nodes[u].nxt[1]);
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
	rt = new_node(30);
	for (int i = 1; i <= n; i++) {
		int a;
		cin >> a;
		work(a);
	}
	dfs(rt);
	cout << ans << endl;
}