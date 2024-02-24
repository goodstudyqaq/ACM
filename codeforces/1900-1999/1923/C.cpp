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
    int n, q;
    cin >> n >> q;
    vector<int> c(n + 1);
    vector<long long> sum1(n + 1), sum2(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> c[i];
        sum1[i] = sum1[i - 1];
        sum2[i] = sum2[i - 1];

        if (c[i] == 1) {
            sum1[i]++;
        } else {
            sum2[i] += c[i] - 1;
        }

    }

    while (q--) {
        int l, r;
        cin >> l >> r;
        if (l == r) {
            cout << "NO" << endl;
            continue;
        }
        int one_num = sum1[r] - sum1[l - 1];
        long long have = sum2[r] - sum2[l - 1];
        if (have >= one_num) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
        


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