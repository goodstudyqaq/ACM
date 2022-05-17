#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

#define endl '\n'
typedef long long ll;

struct fast_ios {
    fast_ios() {
        cin.tie(nullptr);
        ios::sync_with_stdio(false);
        cout << fixed << setprecision(10);
    };
} fast_ios_;

vector<vector<int>> V;
vector<vector<int>> V2;
vector<int> t_in, t_out;
int t;
vector<int> color;
int cnt, flip;
vector<vector<int>> sum;
void dfs(int u, int pre, int c) {
    t_in[u] = t++;
    color[u] = c;
    for (auto v : V[u]) {
        if (color[v] == -1) {
            dfs(v, u, c ^ 1);
            V2[u].push_back(v);
        } else if (t_in[v] < t_in[u]) {
            int diff = (color[u] != color[v]);
            sum[diff][v]--;
            sum[diff][u]++;
            if (!diff) {
                cnt++;
                flip = color[u] ^ 1;
            }
        }
    }
    t_out[u] = t;
}

int choose = -1;
void dfs2(int u, int pre) {
    for (auto v : V2[u]) {
        dfs2(v, u);
        sum[0][u] += sum[0][v];
        sum[1][u] += sum[1][v];
    }

    if (sum[0][u] == cnt && sum[1][u] <= 1) {
        choose = u;
        flip = color[pre] ^ 1;
    }
}

bool is_child(int v, int u) {
    if (t_in[u] <= t_in[v] && t_out[u] >= t_out[v]) return true;
    return false;
}

int n, m;
void init() {
    t = 0;
    cnt = 0, flip = 0;
    choose = -1;
    V = vector(n + 1, vector<int>());
    V2 = vector(n + 1, vector<int>());
    t_in = vector(n + 1, 0);
    t_out = vector(n + 1, 0);
    color = vector(n + 1, -1);
    sum = vector(2, vector(n + 1, 0));
}

void solve() {
    cin >> n >> m;
    init();
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        V[u].push_back(v);
        V[v].push_back(u);
    }
    dfs(1, 0, 0);
    debug(V2);
    debug(color, cnt);
    if (cnt <= 1) {
        cout << "YES" << endl;
        for (int i = 1; i <= n; i++) {
            cout << (color[i] ^ flip);
        }
        cout << endl;
        return;
    }
    dfs2(1, 0);
    if (choose == -1) {
        cout << "NO" << endl;
        return;
    }
    // debug(choose);
    // debug(choose);
    cout << "YES" << endl;
    for (int i = 1; i <= n; i++) {
        cout << (color[i] ^ is_child(i, choose) ^ flip);
    }
    cout << endl;
}

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif
    int T;
    cin >> T;
    while (T--) {
        solve();
    }
}