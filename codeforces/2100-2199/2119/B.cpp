#include <bits/stdc++.h>

#include <algorithm>
#include <cmath>

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
    int n;
    cin >> n;
    long long px, py, qx, qy;
    cin >> px >> py >> qx >> qy;
    long long dis2 = (px - qx) * (px - qx) + (py - qy) * (py - qy);
    double dis = sqrt(dis2);
    vector<double> a(n);
    double sum = 0;
    double mx = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        sum += a[i];
        mx = max(mx, a[i]);
    }
    a.push_back(dis);
    sum += dis;
    mx = max(mx, dis);

    sum -= mx;
    if (mx > sum) {
        cout << "No\n";
    } else {
        cout << "Yes\n";
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