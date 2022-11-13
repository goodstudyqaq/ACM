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
    int n;
    cin >> n;
    vector<int> a(n + 1);
    vector<int> V;
    vector<int> num(n + 1);
    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        V.push_back(i);
        int x = a[i];
        while (x % 2 == 0) {
            cnt++;
            x /= 2;
        }
        x = i;
        while (x % 2 == 0) {
            num[i]++;
            x /= 2;
        }
    }
    debug(cnt);
    debug(num);

    if (cnt >= n) {
        cout << 0 << endl;
        return;
    }
    int need = n - cnt;

    sort(V.begin(), V.end(), [&](int x, int y) {
        return num[x] > num[y];
    });

    for (int i = 0; i < n; i++) {
        int val = num[V[i]];
        cnt += val;
        if (cnt >= n) {
            cout << i + 1 << endl;
            break;
        }
    }
    if (cnt < n) {
        cout << -1 << endl;
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