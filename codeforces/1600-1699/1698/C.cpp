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
    vector<ll> a(n);
    vector<vector<ll>> V(3);
    vector<ll> V2;
    set<ll> S;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        if (a[i] > 0) {
            V[0].push_back(a[i]);
        } else if (a[i] < 0) {
            V[1].push_back(a[i]);
        } else {
            V[2].push_back(a[i]);
        }
        S.insert(a[i]);
    }
    if (V[0].size() >= 3 || V[1].size() >= 3) {
        cout << "NO" << endl;
        return;
    }

    for (int i = 0; i < 3; i++) {
        int sz = min(int(V[i].size()), 3);
        for (int j = 0; j < sz; j++) {
            V2.push_back(V[i][j]);
        }
    }

    for (int i = 0; i < V2.size(); i++) {
        for (int j = i + 1; j < V2.size(); j++) {
            for (int k = j + 1; k < V2.size(); k++) {
                ll tmp = V2[i] + V2[j] + V2[k];
                if (S.count(tmp) == 0) {
                    cout << "NO" << endl;
                    return;
                }
            }
        }
    }
    cout << "YES" << endl;
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