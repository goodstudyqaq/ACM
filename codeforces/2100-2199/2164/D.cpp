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
    int n, kmx;
    cin >> n >> kmx;
    string s, t;
    cin >> s >> t;
    vector<int> pre(n);
    auto get_need = [&]() -> int {
        int s_idx = n - 1;
        int ans = 0;
        for (int i = n - 1; i >= 0; i--) {
            char it = t[i];
            if (s_idx > i) {
                s_idx = i;
            }
            while (s_idx >= 0 && s[s_idx] != it) {
                s_idx--;
            }
            if (s_idx == -1) {
                return -1;
            }
            ans = max(ans, i - s_idx);
            pre[i] = s_idx;
        }
        return ans;
    };

    int need = get_need();
    // debug(need);
    if (need == -1 || need > kmx) {
        cout << -1 << '\n';
        return;
    }

    cout << need << '\n';
    string now = s;

    for (int i = 0; i < need; i++) {
        string go = now;
        for (int j = 1; j < n; j++) {
            int the_pre = pre[j];
            int step = j - the_pre;
            if (i < step) {
                go[j] = now[j - 1];
            }
        }
        cout << go << '\n';
        now = go;
    }
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