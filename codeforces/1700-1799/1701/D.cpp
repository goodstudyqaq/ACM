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
typedef pair<pii, int> piii;
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

    vector<int> b(n + 1);
    // vector<int> a(n + 1);
    // for (int i = 1; i <= n; i++) {
    //     cin >> a[i];
    //     b[i] = i / a[i];
    // }
    vector<piii> V;
    for (int i = 1; i <= n; i++) {
        cin >> b[i];
        // 区间
        int l, r;
        if (b[i] == 0) {
            r = n;
        } else {
            r = i / b[i];
        }
        l = i / (b[i] + 1) + 1;
        V.push_back({{l, r}, i});
    }
    sort(V.begin(), V.end());

    vector<int> ans(n + 1);

    set<pii> S;
    int now_idx = 0;

    for (int i = 1; i <= n; i++) {
        while (now_idx < V.size() && V[now_idx].first.first <= i && V[now_idx].first.second >= i) {
            S.insert({V[now_idx].first.second, V[now_idx].second});
            now_idx++;
        }
        auto it = S.begin();
        ans[it->second] = i;
        S.erase(S.begin());
    }

    for (int i = 1; i <= n; i++) {
        cout << ans[i] << ' ';
    }
    cout << endl;
    // debug(b);
    // for (int i = 1; i <= n; i++) {
    //     cout << i / ans[i] << ' ';
    // }
    // cout << endl;
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