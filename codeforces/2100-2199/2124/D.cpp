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
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    auto a2 = a;
    sort(a2.begin(), a2.end());

    int val = a2[k - 1];
    // 大于等于 val 都可以删掉

    int l = 0, r = n - 1;
    bool f = false;

    int now = k - 1;
    while (now < n && a2[now] == val) {
        now++;
    }
    int can_remove_num = now - (k - 1);
    debug(can_remove_num);
    while (l <= r) {
        debug(l, r);
        if (a[l] == a[r]) {
            l++;
            r--;
        } else {
            if (a[l] < val && a[r] < val) {
                cout << "NO\n";
                return;
            }
            if (a[l] > a[r]) {
                if (a[l] == val) {
                    if (can_remove_num == 0) {
                        cout << "NO\n";
                        return;
                    } else {
                        can_remove_num--;
                        l++;
                    }
                } else {
                    l++;
                }
            } else {
                if (a[r] == val) {
                    if (can_remove_num == 0) {
                        cout << "NO\n";
                        return;
                    } else {
                        can_remove_num--;
                        r--;
                    }
                } else {
                    r--;
                }
            }
        }
    }
    cout << "YES\n";
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