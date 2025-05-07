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
    vector<long long> a(3);
    for (int i = 0; i < 3; i++) {
        cin >> a[i];
    }
    sort(a.begin(), a.end());
    for (int i = 0; i < 3; i++) {
        for (int j = i + 1; j < 3; j++) {
            long long tmp = a[j] - a[i];
            if (tmp % 3 == 0) {
                
                cout << "Yes\n";
                return;
                int k = 0;
                while (k == i || k == j) k++;


                long long times = tmp / 3;
                if (a[k] >= times) {
                    cout << "Yes\n";
                    return;
                } else {
                    long long need = times - a[k];
                    long long need_times = (need + 1) / 2;
                    if (a[i] >= need_times) {
                        cout << "Yes\n";
                        return;
                    }
                }
            }
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