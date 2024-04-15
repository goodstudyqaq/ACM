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
    string x, y;
    cin >> x >> y;

    int n = x.size();

    int now = 0;
    while (now < n && x[now] == y[now]) {
        now++;
    }
    if (now == n) {
        cout << x << endl;
        cout << y << endl;
        return;
    }

    // 让 x 大于 y

    if (x[now] < y[now]) {
        swap(x[now], y[now]);
    }

    for (int i = now + 1; i < n; i++) {
        if (x[i] > y[i]) {
            swap(x[i], y[i]);
        }
    }
    cout << x << endl;
    cout << y << endl;




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