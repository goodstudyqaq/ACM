/*
n*m的矩阵，每个点有一个值，最大的值为p，要求从1依次走到p(即先到等于1的点，再到等于2的点。。)的最小步数
*/
#include <algorithm>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <vector>
using namespace std;
const int maxn = 305;
const int inf = 0x3f3f3f3f;
typedef pair< int, int > pii;
int a[maxn][maxn];
vector< pii > V[maxn * maxn];
bool vis[maxn][maxn];
int d[maxn][maxn];

int tmpd[maxn][maxn];
int dx[4][2] = { -1, 0, 1, 0, 0, 1, 0, -1 };

int main() {
	int n, m, p;
	scanf("%d %d %d", &n, &m, &p);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			scanf("%d", &a[i][j]);
			V[a[i][j]].push_back({ i, j });
		}
	}
	memset(d, inf, sizeof(d));
	for (auto it : V[p]) {
		vis[it.first][it.second] = true;
		d[it.first][it.second] = 0;
	}

	int now = p;
	for (; now > 1; now--) {
		int now_sz = V[now].size();
		int nxt_sz = V[now - 1].size();

		if (now_sz * nxt_sz > n * m) {
			queue< pii > Q;

			for (int i = 1; i <= n; i++) {
				for (int j = 1; j <= m; j++) {
					tmpd[i][j] = inf;
					vis[i][j] = 0;
				}
			}

			for (auto it : V[now]) {
				Q.push(it);
				tmpd[it.first][it.second] = d[it.first][it.second];
				vis[it.first][it.second] = 1;
			}

			while (!Q.empty()) {
				pii x = Q.front();
				Q.pop();
				vis[x.first][x.second] = 0;

				for (int i = 0; i < 4; i++) {
					int tmpx = x.first + dx[i][0];
					int tmpy = x.second + dx[i][1];
					if (tmpx >= 1 && tmpx <= n && tmpy >= 1 && tmpy <= m) {
						if (tmpd[tmpx][tmpy] > tmpd[x.first][x.second] + 1) {
							tmpd[tmpx][tmpy] = tmpd[x.first][x.second] + 1;
							if (!vis[tmpx][tmpy]) {
								vis[tmpx][tmpy] = 1;
								Q.push({ tmpx, tmpy });
							}
						}
					}
				}
			}

			for (auto it : V[now - 1]) {
				d[it.first][it.second] = tmpd[it.first][it.second];
			}

		} else {
			for (auto it : V[now]) {
				for (auto nxt : V[now - 1]) {
					d[nxt.first][nxt.second] = min(d[nxt.first][nxt.second], d[it.first][it.second] + abs(nxt.first - it.first) + abs(nxt.second - it.second));
				}
			}
		}
	}

	int ans = 1e9 + 7;
	for (auto it : V[1]) {
		ans = min(ans, d[it.first][it.second] + abs(it.first - 1) + abs(it.second - 1));
	}
	cout << ans << endl;
}