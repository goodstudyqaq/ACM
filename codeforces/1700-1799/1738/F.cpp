#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

#define endl '\n'
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

struct fast_ios {
    fast_ios(){
        // cin.tie(nullptr);
        // ios::sync_with_stdio(false);
        // cout << fixed << setprecision(10);
    };
} fast_ios_;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    vector<int> idx(n + 1);
    iota(idx.begin(), idx.end(), 0);
    vector<int> color(n + 1, -1);
    sort(idx.begin() + 1, idx.begin() + 1 + n, [&](int x, int y) {
        return a[x] > a[y];
    });
    auto ask = [&](int u) {
        cout << "? " << u << endl;
        fflush(stdout);
        int res;
        cin >> res;
        return res;
    };
    int c = 1;

    int now = 1;
    while (now <= n) {
        while (now <= n && color[idx[now]] != -1) now++;
        if (now > n) break;

        int u = idx[now];
        vector<int> tmp;
        bool flag = false;
        int times = a[u];

        while (times--) {
            int v = ask(u);
            if (color[v] != -1) {
                flag = true;
                color[u] = color[v];
                break;
            } else {
                tmp.push_back(v);
            }
        }

        if (!flag) {
            // 没有碰到之前的
            color[u] = c;
            for (auto it : tmp) {
                color[it] = c;
            }
            c++;
        } else {
            // 碰到了之前涂色的
            for (auto it : tmp) {
                color[it] = color[u];
            }
        }
    }
    cout << "! ";
    for (int i = 1; i <= n; i++) {
        cout << color[i] << ' ';
    }
    cout << endl;
}

int main() {
    // #ifdef LOCAL
    //     freopen("./data.in", "r", stdin);
    // #endif
    int T;
    cin >> T;
    while (T--) {
        solve();
    }
}