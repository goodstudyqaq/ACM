#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

struct fast_ios {
    fast_ios() {
        cin.tie(nullptr);
        ios::sync_with_stdio(false);
        cout << fixed << setprecision(10);
    };
} fast_ios_;

const int maxn = 2e5;

struct Node {
    int sz;
    int nxt[2];
} nodes[maxn * 30];
int root;
int tot;

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif
    int n, m;
    cin >> n >> m;
    root = ++tot;
    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        int now = root;
        for (int j = 29; j >= 0; j--) {
            nodes[now].sz++;
            int w = (a >> j) & 1;
            if (nodes[now].nxt[w] == 0) {
                nodes[now].nxt[w] = ++tot;
            }
            now = nodes[now].nxt[w];
        }
        nodes[now].sz++;
    }
    while (m--) {
        int x, k;
        cin >> x >> k;

        int now = root;
        int res = 0;

        for (int j = 29; j >= 0; j--) {
            int w = (x >> j) & 1;
            if (nodes[nodes[now].nxt[w]].sz >= k) {
                now = nodes[now].nxt[w];
            } else {
                res += (1 << j);
                k -= nodes[nodes[now].nxt[w]].sz;
                now = nodes[now].nxt[w ^ 1];
            }
        }
        cout << res << endl;
    }
}