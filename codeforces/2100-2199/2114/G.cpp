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
    vector<pii> a(n);

    for (int i = 0; i < n; i++) {
        int val;
        cin >> val;
        int two = 1;
        while (val % 2 == 0) {
            val /= 2;
            two *= 2;
        }
        a[i] = {val, two};
    }

    long long mx = 0;
    // a[0] 作为起始位置
    long long now_val_sum = 0;
    vector<long long> vals(n);
    for (int i = 0; i < n; i++) {
        long long val;
        if (i == 0) {
            val = a[i].second;
        } else {
            if (a[i].first != a[i - 1].first) {
                val = a[i].second;
            } else {
                if (a[i].second < a[i - 1].second) {
                    val = a[i].second;
                } else {
                    val = 
                    val = a[i].second - (a[i - 1].second * 2) + 1;
                }
            }
        }
        vals[i] = val;
        now_val_sum += val;
    }
    debug(vals);
    mx = now_val_sum;
    for (int i = 1; i < n; i++) {
        now_val_sum -= vals[i - 1];
        now_val_sum -= vals[i];

        vals[i] = a[i].second;

        if (a[i].first != a[i - 1].first) {
            vals[i - 1] = a[i - 1].second;
        } else {
            if (a[i].second > a[i - 1].second) {
                vals[i - 1] = a[i - 1].second;
            } else {
                vals[i - 1] = a[i - 1].second - (a[i].second * 2) + 1;
            }
        }

        now_val_sum += vals[i - 1];
        now_val_sum += vals[i];
        mx = max(mx, now_val_sum);
    }

    if (k > mx) {
        cout << "NO\n";
    } else {
        cout << "YES\n";
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