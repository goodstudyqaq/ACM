
#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

#define endl '\n'

struct fast_ios {
    fast_ios() {
        cin.tie(nullptr);
        ios::sync_with_stdio(false);
        cout << fixed << setprecision(10);
    };
} fast_ios_;

//边从0到tot-1，点从1到N
//如果有重边的话，在tarjan函数自己加上判断函数即可。
//不管是有向图还是无向图，LOW数组都不能代表点所在的连通分量。
const int maxn = 1e5;
const int maxm = 1e5 + 5;
struct Edge {
    int u, v, next;
    Edge(int _u, int _v, int _nxt) : u(_u), v(_v), next(_nxt) {}
    Edge() {}
} edges[maxm * 2];
int head[maxn], tot;
void addedge(int u, int v) {
    edges[tot] = Edge(u, v, head[u]);
    head[u] = tot++;
}
int DFN[maxn], LOW[maxn], id;
int stk[maxn], tot1;
bool is_cut[maxn];
vector<vector<int>> dcc;
void tarjan(int u) {
    DFN[u] = LOW[u] = ++id;
    stk[tot1++] = u;
    int flag = 0;
    for (int i = head[u]; ~i; i = edges[i].next) {
        int v = edges[i].v;
        if (!DFN[v]) {
            tarjan(v);
            LOW[u] = min(LOW[u], LOW[v]);
            if (LOW[v] == DFN[u]) {
                flag++;
                if (u != 1 || flag > 1) is_cut[u] = true;
                int t;
                dcc.push_back({});
                do {
                    t = stk[tot1 - 1];
                    tot1--;
                    dcc.back().push_back(t);
                } while (t != v);
                dcc.back().push_back(u);
            }
        } else {
            LOW[u] = min(LOW[u], DFN[v]);
        }
    }
}
void init() {
    id = 0;
    tot = 0;
    memset(head, -1, sizeof(head));
    memset(DFN, 0, sizeof(DFN));
    memset(LOW, 0, sizeof(LOW));
    memset(is_cut, 0, sizeof(is_cut));
    dcc.clear();
}

class Solution {
   public:
    long long minimumCost(vector<int>& cost, vector<vector<int>>& roads) {
        init();
        int m = roads.size();
        int n = cost.size();
        for (int i = 0; i < m; i++) {
            int u = roads[i][0], v = roads[i][1];
            u++, v++;
            addedge(u, v);
            addedge(v, u);
        }
        id = 0;
        tarjan(1);

        if (dcc.size() == 1) {
            int idx = min_element(cost.begin(), cost.end()) - cost.begin();
            return cost[idx];
        }

        long long ans = 0;
        int mx = 0;
        for (auto it : dcc) {
            int cut_num = 0;
            int mi = 1e9;
            for (auto it2 : it) {
                if (is_cut[it2])
                    cut_num++;
                else {
                    mi = min(mi, cost[it2 - 1]);
                }
            }
            if (cut_num == 1) {
                ans += mi;
                mx = max(mx, mi);
            }
        }
        return ans - mx;
    }
};
int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif
}