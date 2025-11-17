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
    int k;
    long long x;
    cin >> k >> x;
    long long xc = x;

    vector<int> v;
    while (x) {
        v.push_back(x % 2);
        x /= 2;
    }
    vector<int> idx;
    for (int i = 0; i < v.size(); i++) {
        if (v[i] == 1) {
            idx.push_back(i);
        }
    }

    long long now = 1LL << k;
    long long total = 1LL << (k + 1);
    vector<int> ans;

    int now_idx = 0;

    for (int i = 0; i < idx.size() - 1; i++) {
        int idx1 = idx[i];
        int idx2 = idx[i + 1];

        int diff = idx2 - idx1;

        for (int j = 0; j < diff - 1; j++) {
            ans.push_back(1);
            now /= 2;
        }
        ans.push_back(2);
        long long other = total - now;
        now += other / 2;
    }

    while (now != xc) {
        ans.push_back(1);
        now /= 2;
    }

    cout << ans.size() << '\n';
    for (int i = 0; i < ans.size(); i++) {
        cout << ans[i] << ' ';
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