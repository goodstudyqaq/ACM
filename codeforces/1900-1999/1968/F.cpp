#include <bits/stdc++.h>

#include <algorithm>

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
    vector<int> a(n + 1);
    vector<int> pre_a(n + 1);
    map<int, vector<int>> M;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        pre_a[i] = pre_a[i - 1] ^ a[i];
        M[pre_a[i]].push_back(i);
    }

    while (q--) {
        int l, r;
        cin >> l >> r;

        int len = r - l + 1;

        int val = pre_a[r] ^ pre_a[l - 1];
        if (val == 0) {
            if (len == 1) {
                cout << "NO" << endl;
            } else {
                cout << "YES" << endl;
            }
        } else {
            if (len < 3) {
                cout << "NO" << endl;
            } else {
                int val2 = val ^ pre_a[l - 1];
                int idx1 = lower_bound(M[val2].begin(), M[val2].end(), l) - M[val2].begin();
                if (idx1 == M[val2].size()) {
                    cout << "NO" << endl;
                } else {
                    int the_idx = M[val2][idx1];
                    val2 = val ^ pre_a[the_idx];
                    int idx2 = lower_bound(M[val2].begin(), M[val2].end(), the_idx + 1) - M[val2].begin();
                    if (idx2 == M[val2].size()) {
                        cout << "NO" << endl;
                    } else if (M[val2][idx2] > r) {
                        cout << "NO" << endl;
                    } else {
                        cout << "YES" << endl;
                    }
                }
            }
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