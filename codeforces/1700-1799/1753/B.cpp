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

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif

    int n, x;
    cin >> n >> x;
    vector<int> a(n + 1);

    const int maxm = 5e5 + 5;
    vector<int> num(maxm, 0);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        num[a[i]]++;
    }

    for (int i = 1; i < x; i++) {
        int val = num[i];

        if (val == 0) continue;

        if (val % (i + 1)) {
            cout << "No" << endl;
            return 0;
        }
        int cnt = val / (i + 1);
        num[i] = 0;
        num[i + 1] += cnt;
    }
    cout << "Yes" << endl;
}