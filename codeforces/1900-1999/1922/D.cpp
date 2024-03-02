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
    fast_ios() {
        cin.tie(nullptr);
        ios::sync_with_stdio(false);
        cout << fixed << setprecision(10);
    };
} fast_ios_;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1), d(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = 1; i <= n; i++) {
        cin >> d[i];
    }

    vector<int> l(n + 1), r(n + 1);
    set<int> alive;
    for (int i = 1; i <= n; i++) {
        l[i] = i - 1;
        r[i] = i + 1;
        alive.insert(i);
    }
    r[n] = 0;
    vector<int> vis(n + 1, 0);

    for (int step = 1; step <= n; step++) {
        vector<int> die;
        for (auto v : alive) {
            int sum = 0;

            if (l[v] != 0) {
                sum += a[l[v]];
            }
            if (r[v] != 0) {
                sum += a[r[v]];
            }
            if (sum > d[v]) {
                die.push_back(v);
            }
        }
        cout << die.size() << ' ';
        debug(die);

        for (auto it : die) {
            vis[it] = 1;
        }
        alive.clear();


        for (auto it : die) {
            if (r[it]) {
                l[r[it]] = l[it];

                if (vis[r[it]] == 0) {
                    alive.insert(r[it]);
                }
            }
            if (l[it]) {
                r[l[it]] = r[it];
                if (vis[l[it]] == 0) {
                    alive.insert(l[it]);
                } 
            }
        }
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
    return 0;
}