#include<bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

int n;
vector<int> G[200005];
int siz[200005];
int del[200005];
int cur_h[200005];
int last_lim[200005];
int ans = 0;

void dfs (int u, int p) {
    siz[u] = 1;
    for (int v : G[u]) {
        if (v == p) {
            continue;
        }
        dfs (v, u);
        siz[u] += siz[v];
    }
}

void dfs2 (int u, int p) {
//    printf ("u=%d\n", u);
//    siz[u] = 1;
    vector<pii> G2;
    for (int v : G[u]) {
        if (v == p) {
            continue;
        }
        G2.push_back ({siz[v], v});
    }
    sort (G2.begin(), G2.end());
    G[u].clear();
    for (auto [sizv, v] : G2) {
        G[u].push_back (v);
    }

    for (int v : G[u]) {
        if (v == p) {
            continue;
        }
        dfs2 (v, u);
    }
}

void dfs3 (int u, int p, int lim_height) {
    if (del[u]) {
        return;
    }
//    printf ("u=%d lim=%d\n", u, lim_height);
    if (lim_height == 0) {
        ans += siz[u];
        del[u] = 1;
        cur_h[u] = 0;
//        printf ("del u=%d siz=%d\n", u, siz[u]);
        return;
    }

    if (lim_height >= last_lim[u]) {
        return;
    }

    last_lim[u] = lim_height;

    if (cur_h[u] <= lim_height) {
        return;
    }

    if (G[u].size() == 1) {
        lim_height = min (lim_height, 2);
    }

    cur_h[u] = 1;
//    for (int t = 1; t <= 1; ++t) {
    for (int v : G[u]) {
        if (v == p) {
            continue;
        }
        dfs3 (v, u, lim_height - 1);
        lim_height = min (lim_height, cur_h[v] + 2);  // 最矮的子树是cur，另一科子树最高是cur+1，当前最高是cur+2
        cur_h[u] = max (cur_h[u], cur_h[v] + 1);
    }

    last_lim[u] = lim_height;
//        reverse (G[u].begin(), G[u].end());
//    }
//    printf ("u=%d height=%d\n", u, cur_h[);
    return;
}

int main() {
#ifdef LOCAL
    freopen ("A.in", "r", stdin);
#endif // LOCAL
    scanf ("%d", &n);
    for (int i = 1; i <= n - 1; ++i) {
        int x, y;
        scanf ("%d%d", &x, &y);
        G[x].push_back (y);
        G[y].push_back (x);
    }
    for (int i = 1; i <= n; ++i) {
        cur_h[i] = 1e9 + 5;
        last_lim[i] = 1e9 + 5;
    }
    dfs (1, 1);
    dfs2 (1, 1);
    int pre_ans = ans;
    int lim_height = 1e9;
    while (1) {
//        printf("===\n");
        pre_ans = ans;
        dfs3 (1, 1, lim_height);
        lim_height = cur_h[1];
        if (pre_ans != ans) {
            continue;
        }
        break;
    }
    printf ("%d\n", ans);
}
