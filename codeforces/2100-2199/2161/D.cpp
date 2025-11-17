#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

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
    vector<vector<int>> V(n + 1);
    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        V[a].push_back(i);
    }

    int ed = n;
    while (ed >= 0 && V[ed].size() == 0) {
        ed--;
    }
    set<int> S;
    for (auto it : V[ed]) {
        S.insert(it);
    }
    int ans = 0;
    for (int i = ed - 1; i >= 0; i--) {
        int sz = V[i].size();
        vector<int> tmp;
        for (int j = sz - 1; j >= 0; j--) {
            int loc = V[i][j];
            auto it = S.lower_bound(loc);
            if (it == S.end()) {
                tmp.push_back(loc);
            } else {
                ans++;
                S.erase(it);
            }
        }
        S.clear();
        for (auto it : tmp) {
            S.insert(it);
        }
    }
    cout << ans << '\n';
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