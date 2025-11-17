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
    int n;
    cin >> n;
    vector<int> a(n);
    map<int, int> cnt;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        cnt[a[i]]++;
    }
    long long A = 0, B = 0;

    vector<int> V;
    for (auto [val, num] : cnt) {
        // val 出现了 num 次
        long long tmp = 1LL * val / 2 * num;
        A += tmp;
        B += tmp;
        if (val % 2) {
            V.push_back(num);
        }
    }
    sort(V.begin(), V.end());
    reverse(V.begin(), V.end());
    for (int i = 0; i < V.size(); i++) {
        if (i % 2 == 0) {
            A += V[i];
        } else {
            B += V[i];
        }
    }
    cout << A << ' ' << B << '\n';
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