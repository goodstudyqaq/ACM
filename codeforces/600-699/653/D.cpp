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

const int maxn = 1e5 + 1000;
const int maxm = maxn;
const int maxv = maxn;
const int inf = 0x3f3f3f3f;
struct Edge {
	int from, to, cap, flow;
	Edge(int u, int v, int c, int f)
		: from(u), to(v), cap(c), flow(f) {}
	Edge() {}
};
struct Dinic {
	int n, m, s, t;
	vector< Edge > edges;
	vector< int > G[maxv + 50];
	bool vis[maxv + 50];
	int d[maxv + 50];
	int cur[maxv + 50];

	void AddEdge(int from, int to, int cap) {
		edges.push_back(Edge(from, to, cap, 0));
		edges.push_back(Edge(to, from, 0, 0));
		m = edges.size();
		G[from].push_back(m - 2);
		G[to].push_back(m - 1);
	}

	void init(int n) {
		for (int i = 0; i <= n; i++) G[i].clear();
		edges.clear();
	}

	bool BFS() {
		memset(vis, 0, sizeof(vis));
		queue< int > Q;
		Q.push(s);
		d[s] = 0;
		vis[s] = 1;
		while (!Q.empty()) {
			int x = Q.front();
			Q.pop();
			for (int i = 0; i < G[x].size(); i++) {
				Edge& e = edges[G[x][i]];
				if (!vis[e.to] && e.cap > e.flow) {
					vis[e.to] = 1;
					d[e.to] = d[x] + 1;
					Q.push(e.to);
				}
			}
		}
		return vis[t];
	}

	int DFS(int x, int a) {
		if (x == t || a == 0) return a;
		long long flow = 0, f;
		for (int& i = cur[x]; i < G[x].size(); i++) {
			Edge& e = edges[G[x][i]];
			if (d[x] + 1 == d[e.to] && (f = DFS(e.to, min(a, e.cap - e.flow))) > 0) {
				e.flow += f;
				edges[G[x][i] ^ 1].flow -= f;
				flow += f;
				a -= f;
				if (a == 0) break;
			}
		}
		return flow;
	}
	long long Maxflow(int s, int t) {
		//cout << edges.size() << endl;
		this->s = s;
		this->t = t;
		long long flow = 0;
		while (BFS()) {
			memset(cur, 0, sizeof(cur));
			flow += DFS(s, inf);
		}
		return flow;
	}

} ans;

typedef pair< int, int > pii;
typedef pair< pii, int > piii;
piii edges[maxm];

int n, m, x;
void build(double val) {
	double avg = val / x;
	ans.init(n);
	for (int i = 1; i <= m; i++) {
		int u = edges[i].first.first;
		int v = edges[i].first.second;
		int w = edges[i].second;
		int val = min(1LL * x, ( long long )(w / avg));
		// debug(u, v, val);
		ans.AddEdge(u, v, val);
	}
}

bool check(double val) {
	int start = 1, end = n;
	long long res = ans.Maxflow(start, end);
	// debug(res);
	if (res >= x) return true;
	return false;
}

int main() {
	freopen("data.in", "r", stdin);
	scanf("%d %d %d", &n, &m, &x);
	int u, v, w;
	int mxw = 0;
	for (int i = 1; i <= m; i++) {
		scanf("%d %d %d", &u, &v, &w);
		edges[i] = { { u, v }, w };
		mxw = max(mxw, w);
	}

	double l = 0, r = 1e11;

	for (int t = 1; t <= 100; t++) {
		double mid = (l + r) / 2.0;

		build(mid);
		if (check(mid)) {
			l = mid;
		} else {
			r = mid;
		}
	}
	printf("%.6f\n", l);
	return 0;
}