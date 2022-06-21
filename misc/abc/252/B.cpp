#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

#define endl '\n'
typedef long long ll;

struct fast_ios {
    fast_ios() {
        cin.tie(nullptr);
        ios::sync_with_stdio(false);
        cout << fixed << setprecision(10);
    };
} fast_ios_;

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif
    int n, k;
    cin >> n >> k;
    int mx = 0;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        mx = max(mx, a[i]);
    }
    set<int> S;
    for (int i = 0; i < n; i++) {
        if (a[i] == mx) {
            S.insert(i);
        }
    }

    bool flag = false;
    for (int i = 0; i < k; i++) {
        int v;
        cin >> v;
        v--;
        if (S.count(v)) {
            flag = true;
        }
    }

    cout << (flag ? "Yes" : "No") << endl;
    return 0;
}