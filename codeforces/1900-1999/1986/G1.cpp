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
    vector<int> g(n + 1);
    vector<int> need(n + 1), have(n + 1);
    map<int, vector<int>> M;
    map<int, map<int, int>> M2;
    long long ans = 0;
    int ans2 = 0;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        g[i] = gcd(a[i], i);
        need[i] = i / g[i];
        have[i] = a[i] / g[i];
        M[have[i]].push_back(i);
        M2[need[i]][have[i]]++;
        if (need[i] == 1) ans2++;
    }

    for (auto it : M2) {
        int x = it.first;
        map<int, int> M3;
        for (int j = x; j <= n; j += x) {
            for (auto it : M[j]) {
                M3[need[it]]++;
            }
        }

        for (auto it2 : M3) {
            int x2 = it2.first;
            long long times = it2.second;
            long long sub_ans = 0;
            for (int j = x2; j <= n; j += x2) {
                if (it.second.count(j)) {
                    sub_ans += it.second[j];
                }
            }
            ans += sub_ans * times;
        }
    }

    ans -= ans2;
    ans /= 2;
    // ans += ans2;

    cout << ans << endl;
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