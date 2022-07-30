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
    int n, m, k;
    cin >> n >> m >> k;
    vector<int> num(k + 1);
    for (int i = 1; i <= k; i++) {
        cin >> num[i];
    }

    auto check = [&](int n, int m) -> bool {
        int res = 0;
        vector<int> V;
        for (int i = 1; i <= k; i++) {
            int tmp = num[i] / n;
            if (tmp <= 1) continue;
            V.push_back(tmp);
        }

        sort(V.begin(), V.end());
        reverse(V.begin(), V.end());

        int ct = 0;
        for (int i = 0; i < V.size(); i++) {
            if (V[i] > 2) {
                ct += V[i] - 2;
            }
            res += V[i];
            if (res >= m) break;
        }
        if (res < m) return false;
        if (res == m) return true;
        int tmp = res - m;
        if (ct >= tmp) return true;
        return false;
    };

    if (check(n, m)) {
        cout << "Yes" << endl;
    } else if (check(m, n)) {
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
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
}