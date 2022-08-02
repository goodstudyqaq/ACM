#include <bits/stdc++.h>
using namespace std;
const int maxn = 55;
bool mp[maxn][maxn];
int best, n, num[maxn];
bool dfs(int* adj, int total, int cnt) {
	int t[maxn], k;
	if (total == 0) {
		if (cnt > best) {
			best = cnt;
			return true;  //剪枝4
		}
		return false;
	}
	for (int i = 0; i < total; ++i) {
		if (cnt + total - i <= best) return false;	  //剪枝1
		if (cnt + num[adj[i]] <= best) return false;  //剪枝3
		k = 0;
		for (int j = i + 1; j < total; ++j)
			if (mp[adj[i]][adj[j]]) t[k++] = adj[j];
		//扫描与u相连的顶点中与当前要选中的adj[i]相连的顶点adj[j]并存储到数组t[]中，数量为k
		if (dfs(t, k, cnt + 1)) return true;
	}
	return false;
}
int MaximumClique() {
	int adj[maxn], k;
	best = 0;
	for (int i = n; i >= 1; --i) {
		k = 0;
		for (int j = i + 1; j <= n; ++j)
			if (mp[i][j]) adj[k++] = j;
		//得到当前点i的所有相邻点存入adj
		dfs(adj, k, 1);	 //每次dfs相当于必选当前i点看是否能更新best
		num[i] = best;
	}
	return best;
}

struct Node {
	int val;
	int idx;
};

int main() {
	freopen("data.in", "r", stdin);
	ios::sync_with_stdio(false);
	cin.tie(0);
	int num, m;
	cin >> num >> m;
	map< string, int > M;
	int mcnt = 0;
	vector< Node > V(num + 1);
	for (int i = 1; i <= num; i++) {
		cin >> V[i].val;
		string s;
		if (V[i].val == 2) {
			cin >> s;
			if (!M.count(s)) {
				M[s] = ++mcnt;
			}
			V[i].idx = M[s];
		}
	}

	int now = 1;
	while (now <= num) {
		// cout << now << endl;
		int go = now;
		while (go <= num && V[go].val == 1) go++;
		int go2 = go;
		while (go2 <= num && V[go2].val == 2) go2++;
		for (int i = go; i < go2; i++) {
			for (int j = i + 1; j < go2; j++) {
				if (V[i].idx == V[j].idx) continue;
				mp[V[i].idx][V[j].idx] = mp[V[j].idx][V[i].idx] = 1;
			}
		}
		now = go2;
	}

	for (int i = 1; i <= mcnt; i++) {
		for (int j = i + 1; j <= mcnt; j++) {
			mp[i][j] ^= 1;
		}
	}
	n = mcnt;
	cout << MaximumClique() << endl;
	return 0;
}
