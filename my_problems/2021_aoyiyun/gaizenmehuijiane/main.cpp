#include <bits/stdc++.h>

using namespace std;

struct HeapNode {
	int u;
	long long d;
	bool operator<(const HeapNode& b) const {
		return d > b.d;
	}
};
struct Edge {
	int u, v, w, nxt;
};
const int maxm = 2e5 + 1;
const int maxn = 1e5 + 1;
const long long inf = 1e10 + 1;
int head[maxn];
Edge edges[maxm];
int e_cnt;

void add_edge(int u, int v, int w) {
	edges[e_cnt] = (Edge){ u, v, w, head[u] };
	head[u] = e_cnt++;
}

int n, m, s, t1, t2;
bool vis[maxn];
void dijkstra(int s, long long* d) {
	for (int i = 1; i <= n; i++) {
		d[i] = inf;
		vis[i] = 0;
	}
	d[s] = 0;
	priority_queue< HeapNode > Q;
	Q.push((HeapNode){ s, 0 });

	while (!Q.empty()) {
		HeapNode it = Q.top();
		Q.pop();
		if (vis[it.u]) continue;
		vis[it.u] = true;
		int u = it.u;
		for (int i = head[u]; ~i; i = edges[i].nxt) {
			int v = edges[i].v;
			if (d[v] > d[u] + edges[i].w) {
				d[v] = d[u] + edges[i].w;
				Q.push((HeapNode){ v, d[v] });
			}
		}
	}
}

long long d1[maxn], d2[maxn], d3[maxn];

int main() {
#ifdef LOCAL
	freopen("data7.in", "r", stdin);
	freopen("data7.out", "w", stdout);
#endif
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n >> m >> s >> t1 >> t2;
	memset(head, -1, sizeof(head));
	for (int i = 1; i <= m; i++) {
		int u, v, w;
		cin >> u >> v >> w;
		add_edge(u, v, w);
		add_edge(v, u, w);
	}

	dijkstra(s, d1);
	dijkstra(t1, d2);
	dijkstra(t2, d3);

	long long ans = 2e10 + 1;
	for (int i = 1; i <= n; i++) {
		ans = min(ans, d1[i] + d2[i] + d3[i]);
	}
	cout << ans << endl;
	return 0;
}