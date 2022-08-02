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

const int maxn = 51;
const int INF = 0x3f3f3f3f;

struct Edge {
	int from, to, cap, flow, cost;
	Edge(int u, int v, int c, int f, int w)
		: from(u), to(v), cap(c), flow(f), cost(w) {}
};

int n, k;

struct MCMF {
	int n, m;
	vector< Edge > edges;
	vector< int > G[maxn];
	int inq[maxn];
	int d[maxn];
	int p[maxn];
	int a[maxn];

	void init(int n) {
		this->n = n;
		for (int i = 0; i < n; i++) G[i].clear();
		edges.clear();
	}

	void AddEdge(int from, int to, int cap, int cost) {
		edges.push_back(Edge(from, to, cap, 0, cost));
		edges.push_back(Edge(to, from, 0, 0, -cost));
		m = edges.size();
		G[from].push_back(m - 2);
		G[to].push_back(m - 1);
	}

	bool BellmanFord(int s, int t, int& flow, long long& cost) {
		for (int i = 0; i < n; i++) d[i] = INF;
		memset(inq, 0, sizeof(inq));
		d[s] = 0;
		inq[s] = 1;
		p[s] = 0;
		a[s] = INF;
		queue< int > Q;
		Q.push(s);
		while (!Q.empty()) {
			int u = Q.front();
			Q.pop();
			inq[u] = 0;
			for (int i = 0; i < G[u].size(); i++) {
				Edge& e = edges[G[u][i]];
				if (e.cap > e.flow && d[e.to] > d[u] + e.cost) {
					d[e.to] = d[u] + e.cost;
					p[e.to] = G[u][i];
					a[e.to] = min(a[u], e.cap - e.flow);
					if (!inq[e.to]) {
						Q.push(e.to);
						inq[e.to] = 1;
					}
				}
			}
		}
		if (d[t] == INF) return false;

		int now_ct = d[t];
		int now_flow = a[t];

		if (now_ct == 0) {
			flow += a[t];
			cost += ( long long )d[t] * a[t];
			for (int u = t; u != s; u = edges[p[u]].from) {
				edges[p[u]].flow += a[t];
				edges[p[u] ^ 1].flow -= a[t];
			}
			return true;
		} else {
			now_flow = min(now_flow, k / now_ct);
			if (now_flow == 0) return false;
			flow += now_flow;
			cost += now_flow * now_ct;
			k = k - now_flow * now_ct;
			for (int u = t; u != s; u = edges[p[u]].from) {
				edges[p[u]].flow += now_flow;
				edges[p[u] ^ 1].flow -= a[t];
			}
			return true;
		}
	}

	int MincostMaxflow(int s, int t, long long& cost) {
		int flow = 0;
		cost = 0;
		while (BellmanFord(s, t, flow, cost))
			;
		return flow;
	}
} m;

int main() {
#ifdef LOCAL
	freopen("data.in", "r", stdin);
#endif
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n >> k;
	m.init(n + 1);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			int w;
			cin >> w;
			if (w) {
				m.AddEdge(i, j, w, 0);
				m.AddEdge(i, j, 1000000, 1);
			}
		}
	}
	long long ct;
	cout << m.MincostMaxflow(1, n, ct) << endl;
	return 0;
}