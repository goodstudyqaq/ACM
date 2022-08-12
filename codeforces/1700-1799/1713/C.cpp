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

vector<int> num;
void init() {
    for (int i = 0; 1LL * i * i <= 2e5 + 1; i++) {
        num.push_back(i * i);
    }
}

void solve() {
    int n;
    cin >> n;

    vector<int> ans(n);
    int sz = num.size();

    auto work = [&](int idx, int val) -> int {
        int tmp = val - idx;
        for (int i = tmp; i <= idx; i++) {
            ans[i] = val - i;
        }
        return tmp - 1;
    };

    for (int i = n - 1; i >= 0;) {
        int idx = lower_bound(num.begin(), num.end(), i) - num.begin();
        // debug(i, num[idx]);
        i = work(i, num[idx]);
    }

    for (int i = 0; i < n; i++) {
        cout << ans[i] << ' ';
    }
    cout << endl;
}

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif
    init();
    int T;
    cin >> T;
    while (T--) {
        solve();
    }
}