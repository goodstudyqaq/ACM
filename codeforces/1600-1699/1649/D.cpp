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

void solve() {
    int n, c;
    cin >> n >> c;
    vector<int> sum(c + 1);
    for (int i = 1; i <= n; i++) {
        int a;
        cin >> a;
        sum[a]++;
    }
    for (int i = 1; i <= c; i++) {
        sum[i] += sum[i - 1];
    }

    for (int i = 1; i <= c; i++) {
        if (sum[i] - sum[i - 1] == 0) continue;

        for (int j = 1; j * i <= c; j++) {
            int r = min(i * (j + 1) - 1, c);
            if (sum[r] - sum[j * i - 1]) {
                if (sum[j] - sum[j - 1] == 0) {
                    cout << "No" << endl;
                    return;
                }
            }
        }
    }
    cout << "Yes" << endl;
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