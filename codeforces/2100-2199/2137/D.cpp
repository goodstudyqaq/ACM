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
    vector<int> b(n);
    map<int, int> cnt;
    for (int i = 0; i < n; i++) {
        cin >> b[i];
        cnt[b[i]]++;
    }

    for (auto it : cnt) {
        int times = it.first;
        int num = it.second;
        if (num % times) {
            cout << -1 << '\n';
            return;
        }
    }
    int now = 1;
    map<int, pair<int, int>> ans;
    for (int i = 0; i < n; i++) {
        int times = b[i];
        if (ans.count(times) && ans[times].first > 0) {
            cout << ans[times].second << ' ';
            ans[times].first--;
        } else {
            ans[times].first = times - 1;
            ans[times].second = now++;
            cout << ans[times].second << ' ';
        }
    }
    cout << '\n';
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