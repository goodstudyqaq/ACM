#include <bits/stdc++.h>

#include <numeric>

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

    vector<pll> V(n);
    long long ans = 0;
    for (int i = 0; i < n; i++) {
        cin >> V[i].first >> V[i].second;
        ans += V[i].second - V[i].first;
    }
    debug(ans);

    vector<pll> V2(n);
    for (int i = 0; i < n; i++) {
        ans -= V[i].first;
        V2[i] = {V[i].first + V[i].second, i};
    }
    sort(V2.begin(), V2.end());
    int half = n / 2;

    if (n % 2 == 0) {
        for (int i = n - 1; i >= n - half; i--) {
            ans += V2[i].first;
        }
        cout << ans << '\n';
    } else {
        long long mx_ans = ans;
        long long tmp = 0;
        for (int i = n - 1; i >= n - half; i--) {
            tmp += V2[i].first;
        }
        long long tmp2 = tmp + V2[n - half - 1].first;

        for (int i = 0; i < n; i++) {
            // 忽略 i
            if (i < n - half) {
                mx_ans = max(mx_ans, ans + V[V2[i].second].first + tmp);
            } else {
                mx_ans = max(mx_ans, ans + V[V2[i].second].first + tmp2 - (V[V2[i].second].first + V[V2[i].second].second));
            }
        }
        cout << mx_ans << '\n';
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