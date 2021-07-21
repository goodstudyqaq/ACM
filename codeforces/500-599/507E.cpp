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

typedef pair< int, int > pii;
const int inf = 1e5 + 1;

struct Edge {
	int u, v, flag;
	int nxt;
	int idx;
	Edge(int _u, int _v, int _f, int _nxt, int _idx)
		: u(_u), v(_v), flag(_f), nxt(_nxt), idx(_idx) {}
	Edge() {}
};
vector< int > head;
vector< Edge > edges;
int ecnt;

void add_edge(int u, int v, int flag) {
	edges[ecnt] = Edge(u, v, flag, head[u], ecnt);
	head[u] = ecnt++;
}

int main() {
#ifdef LOCAL
	freopen("data.in", "r", stdin);
#endif
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n, m;
	cin >> n >> m;
	edges.resize(m * 2);
	head.resize(n + 1, -1);

	for (int i = 1; i <= m; i++) {
		int u, v, f;
		cin >> u >> v >> f;
		add_edge(u, v, f);
		add_edge(v, u, f);
	}

	vector< int > d(n + 1, inf);
	vector< int > one(n + 1, 0);

	d[1] = 0;

	vector< int > pre(n + 1, -1);
	vector< int > vis(m * 2, 0);
	queue< int > Q;
	Q.push(1);

	while (!Q.empty()) {
		int u = Q.front();
		Q.pop();
		for (int i = head[u]; ~i; i = edges[i].nxt) {
			int v = edges[i].v;
			int f = edges[i].flag;
			if (d[v] > d[u] + 1) {
				d[v] = d[u] + 1;
				one[v] = one[u] + f;
				pre[v] = edges[i].idx;
				Q.push(v);
			} else if (d[v] == d[u] + 1) {
				if (one[v] < one[u] + f) {
					one[v] = one[u] + f;
					pre[v] = edges[i].idx;
				}
			}
		}
	}

	debug(d[n], one[n]);

	int now = n;
	vector< int > ans;
	while (now != 1) {
		int eidx = pre[now];
		vis[eidx] = vis[eidx ^ 1] = 1;
		if (edges[eidx].flag == 0) {
			ans.push_back(eidx);
		}
		now = edges[eidx].u;
		debug(now);
	}

	for (int i = 0; i < 2 * m; i += 2) {
		if (vis[i] == 0 && edges[i].flag == 1) {
			ans.push_back(i);
		}
	}
	cout << ans.size() << endl;
	for (int i = 0; i < ans.size(); i++) {
		int idx = ans[i];
		cout << edges[idx].u << ' ' << edges[idx].v << ' ' << (edges[idx].flag ^ 1) << endl;
	}
	return 0;
}