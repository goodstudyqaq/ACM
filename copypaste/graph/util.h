#include <bits/stdc++.h>
using namespace std;
/* 
https://codeforces.com/contest/1695/problem/E
特别的遍历图，能保证 stk 里有 2k + 1 个点，且第一个和最后一个相等，[2t, 2t + 1] 和 [2t - 1, 2t] 都是一条边
*/
vector<int> stk;
vector<int> vis;
vector<int> vis2;
typedef pair<int, int> pii;
vector<vector<pii>> V;
void dfs(int u) {
    stk.emplace_back(u);
    if (vis[u]) return;
    vis[u] = 1;

    for (auto e : V[u]) {
        if (vis2[e.second]) continue;
        vis2[e.second] = 1;
        dfs(e.first);
        stk.emplace_back(u);
    }
}
