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

int n = 44;
vector<ll> f, sumf;
void init() {
    f = vector(n, 0LL);
    sumf = vector(n, 0LL);
    f[0] = 1, f[1] = 1;
    sumf[0] = 1, sumf[1] = 2;
    for (int i = 2; i < n; i++) {
        f[i] = f[i - 1] + f[i - 2];
        sumf[i] = f[i] + sumf[i - 1];
    }
}

void solve() {
    int k;
    cin >> k;
    ll sum = 0;
    vector c = vector(k, 0LL);
    for (int i = 0; i < k; i++) {
        cin >> c[i];
        sum += c[i];
    }
    int idx = -1;
    for (int i = 0; i < n; i++) {
        if (sum == sumf[i]) {
            idx = i;
            break;
        }
    }
    if (idx == -1) {
        cout << "NO" << endl;
        return;
    }

    int last_idx = -1;
    while (idx >= 0) {
        ll need = f[idx];
        int choose = -1;
        for (int i = 0; i < k; i++) {
            if (c[i] >= need && i != last_idx) {
                if (choose == -1 || c[i] > c[choose]) {
                    choose = i;
                }
            }
        }
        if (choose == -1) {
            cout << "NO" << endl;
            return;
        }
        c[choose] -= need;
        idx--;
        last_idx = choose;
    }
    cout << "YES" << endl;
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