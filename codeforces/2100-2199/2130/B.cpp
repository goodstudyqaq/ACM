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
    int n, s;
    cin >> n >> s;
    const int m = 2;
    vector<int> cnt(m + 1);
    int sum = 0;
    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        cnt[a]++;
        sum += a;
    }
    if (sum == s) {
        cout << -1 << '\n';
        return;
    }

    if (s < sum) {
        for (int i = 0; i <= m; i++) {
            for (int j = 0; j < cnt[i]; j++) {
                cout << i << ' ';
            }
        }
        cout << '\n';
        return;
    }

    // s > sum

    int val = s - sum;
    if (val > 1) {
        cout << -1 << '\n';
        return;
    }



    for (int i = 0; i < cnt[0]; i++) {
        cout << 0 << ' ';
    }
    for (int i = 0; i < cnt[2]; i++) {
        cout << 2 << ' ';
    }
    for (int i = 0; i < cnt[1]; i++) {
        cout << 1 << ' ';
    }
    cout << '\n';

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