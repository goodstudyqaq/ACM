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
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    int m = sqrt(n) + 1;
    int ans = 1;

    auto work = [&](int len) {
        set<int> S;
        for (int i = 0; i < len; i++) {
            S.insert(a[i]);
        }

        int res = 1;

        int now = len;

        while (now < n) {
            set<int> S2;
            int go = now;
            int need = S.size();
            while (go < n && need) {
                int val = a[go];
                if (S.count(val) && S2.count(val) == 0) {
                    need--;
                }
                S2.insert(val);
                go++;
            }

            if (need) {
                break;
            }
            res++;
            S = S2;
            now = go;
        }
        return res;
    };
    ans = work(1);

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