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
    vector<int> p(n + 1);
    set<int> S;
    for (int i = 1; i <= n; i++) {
        cin >> p[i];
        S.insert(p[i]);
    }
    int l = -1, r = -1;
    vector<int> zero;
    for (int i = 1; i <= n; i++) {
        if (p[i] != 0 && p[i] != i) {
            if (l == -1) {
                l = i;
            }
            r = i;
        }
        if (p[i] == 0) {
            zero.push_back(i);
        }
    }

    if (zero.size() <= 1) {
        if (l == -1) {
            cout << 0 << '\n';
        } else {
            if (zero.size() == 0) {
                cout << r - l + 1 << '\n';
            } else {
                int miss = 1;
                while (S.count(miss)) {
                    miss++;
                }
                if (miss != zero[0]) {
                    if (l == -1) {
                        l = zero[0];
                        r = zero.back();
                    } else {
                        l = min(l, zero[0]);
                        r = max(r, zero.back());
                    }
                }
                cout << r - l + 1 << '\n';
            }
        }
        return;
    }

    if (l == -1) {
        l = zero[0];
        r = zero.back();
    } else {
        l = min(l, zero[0]);
        r = max(r, zero.back());
    }

    cout << r - l + 1 << '\n';
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