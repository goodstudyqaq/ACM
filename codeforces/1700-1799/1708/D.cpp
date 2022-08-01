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
    vector<int> a;
    int zero = 0;
    for (int i = 0; i < n; i++) {
        int the_a;
        cin >> the_a;
        if (the_a == 0)
            zero++;
        else
            a.push_back(the_a);
    }
    if (zero == n) {
        cout << 0 << endl;
        return;
    }

    for (int i = 1; i < n; i++) {
        sort(a.begin(), a.end());
        int a_sz = a.size();
        a.resize(unique(a.begin(), a.end()) - a.begin());
        if (a.size() == 1) {
            if (zero) {
                cout << a[0] << endl;
            } else {
                cout << 0 << endl;
            }
            return;
        }
        debug(a, zero);
        int a_sz2 = a.size();
        int add_zero = a_sz - a_sz2;
        int tmp = a[0];
        for (int i = 1; i < a.size(); i++) {
            a[i - 1] = a[i] - a[i - 1];
        }
        a.pop_back();
        if (zero) zero--, a.push_back(tmp);
        zero += add_zero;
    }
    cout << a[0] << endl;
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