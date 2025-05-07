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
    vector<int> a(n + 1);
    set<int> S;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        S.insert(i);
    }

    int now = 1;
    int l = 1, r = n;
    vector<int> ans(n + 1);
    while (S.size() > 1) {
        debug(S);
        vector<int> idx;
        set<int>::iterator itor = S.begin();

        while (itor != S.end()) {
            auto go = itor;

            while (go != S.end() && a[*go] != now) go++;

            if (go == S.end()) break;

            auto go2 = go;

            int cnt = 0;
            while (go2 != S.end() && a[*go2] == now) go2++, cnt++;

            if (go2 == S.end()) {
                if (now % 2) {
                    int val = r - cnt + 1;
                    for (auto it = go; it != go2; it++) {
                        ans[*it] = val++;
                    }
                    r -= cnt;
                } else {
                    int val = l + cnt - 1;
                    for (auto it = go; it != go2; it++) {
                        ans[*it] = val--;
                    }
                    l += cnt;
                }
            } else {
                if (now % 2) {
                    for (auto it = go; it != go2; it++) {
                        ans[*it] = r--;
                    }
                } else {
                    for (auto it = go; it != go2; it++) {
                        ans[*it] = l++;
                    }
                }
            }
            itor = go2;
        }

        itor = S.begin();
        for (; itor != S.end();) {
            if (a[*itor] == now) {
                itor = S.erase(itor);
            } else {
                itor++;
            }
        }
        now++;
    }
    ans[*S.begin()] = l;
    for (int i = 1; i <= n; i++) {
        cout << ans[i] << ' ';
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