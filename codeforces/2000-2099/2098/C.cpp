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
    sort(a.begin(), a.end());
    map<int, int> cnt;
    for (auto it : a) {
        cnt[it]++;
    }

    for (int i = 0; i < n; i++) {
        if (cnt[a[i]] >= 4) {
            cout << "Yes\n";
            return;
        }
    }

    int now = 0;
    while (now < n) {
        int val = a[now];
        if (cnt[val] >= 2) {
            int go = now + 1;
            while (go < n && a[go] == a[now]) go++;
            while (go < n && a[go] - a[go - 1] <= 1) {
                if (cnt[a[go]] >= 2) {
                    cout << "Yes\n";
                    return;
                }
                go++;
            }
            now = go;
        } else {
            now++;
        }
    }
    cout << "No\n";
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