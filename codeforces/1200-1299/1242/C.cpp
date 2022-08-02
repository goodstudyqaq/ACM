#include <bits/stdc++.h>
using namespace std;

const int maxn = 16;
vector< long long > V[maxn];
long long sum[maxn];
long long all;
vector< long long > b, c;
map< long long, int > M;

int k;
bool vis[1 << maxn];

int get_circle(int idx, long long v, int f) {
	long long now = v;
	int now_idx = idx;
	int now_f = f;
	while (true) {
		b[now_idx] = now;
		now_f |= (1 << now_idx);
		long long need = all - (sum[now_idx] - now);
		if (!M.count(need)) return -1;
		int nxt_idx = M[need];
		c[nxt_idx] = now_idx + 1;
		if (need == v) {
			return now_f;
		}
		if ((now_f >> nxt_idx) & 1) return -1;

		now = need;
		now_idx = nxt_idx;
	}
	return -1;
}

void dfs(int u, int f) {
	if (u == k) {
		puts("Yes");
		for (int j = 0; j < k; j++) {
			printf("%lld %lld\n", b[j], c[j]);
		}
		exit(0);
	}
	if (vis[f]) {
		return;
	}
	if ((f >> u) & 1) {
		dfs(u + 1, f);
	} else {
		vector< long long > tb(b);
		vector< long long > tc(c);
		for (int i = 0; i < V[u].size(); i++) {
			int tmpf = get_circle(u, V[u][i], f);
			if (tmpf != -1)
				dfs(u + 1, tmpf);
			b = tb;
			c = tc;
		}
		vis[f] = 1;
	}
}

int main() {
	scanf("%d", &k);
	for (int i = 0; i < k; i++) {
		int n;
		scanf("%d", &n);
		for (int j = 1; j <= n; j++) {
			long long u;
			scanf("%lld", &u);
			V[i].push_back(u);
			M[u] = i;
			sum[i] += u;
		}
		all += sum[i];
	}

	if (all % k) {
		puts("No");
		return 0;
	}
	all /= k;
	b.resize(k);
	c.resize(k);
	dfs(0, 0);
	puts("No");
}