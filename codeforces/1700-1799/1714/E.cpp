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
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n; i++) {
        if (a[i] % 10 == 0) {
            for (int j = 0; j < n; j++) {
                if (a[j] != a[i] && a[j] != a[i] - 5) {
                    cout << "No" << endl;
                    return;
                }
            }
            cout << "Yes" << endl;
            return;
        } else if (a[i] % 10 == 5) {
            for (int j = 0; j < n; j++) {
                if (a[j] != a[i] && a[j] != a[i] + 5) {
                    cout << "No" << endl;
                    return;
                }
            }
            cout << "Yes" << endl;
            return;
        }
    }

    // 全部变成 2

    set<int> S;
    for (int i = 0; i < n; i++) {
        while (a[i] % 10 != 2) {
            a[i] += (a[i] % 10);
        }
        S.insert(a[i]);
    }
    if (S.size() == 1) {
        cout << "Yes" << endl;
        return;
    }

    int val = *S.begin();
    for (auto it : S) {
        if ((it - val) % 20 != 0) {
            cout << "No" << endl;
            return;
        }
    }
    cout << "Yes" << endl;
    return;
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