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

vector<bool> vis;

int n;
int times;
vector<int> now;
void dfs(int v1, int v2, int d) {
    if (d == n + 1) {
        for (auto v : now) {
            cout << v << ' ';
        }
        cout << endl;
        times++;
        return;
    }
    if (times == n) return;
    int sum = v1 + v2;

    for (int i = 1; i <= n; i++) {
        if (vis[i] == 0 && i != sum) {
            vis[i] = 1;
            now.push_back(i);
            dfs(v2, i, d + 1);
            vis[i] = 0;
            now.pop_back();
        }
    }
}

void solve() {
    cin >> n;
    vis = vector(n + 1, false);
    times = 0;
    dfs(0, 0, 1);
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