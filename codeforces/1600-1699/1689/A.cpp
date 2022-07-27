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
    string s1, s2;
    cin >> s1 >> s2;
    sort(s1.begin(), s1.end());
    sort(s2.begin(), s2.end());

    int l1 = 0, l2 = 0;
    int comb = 0;
    string ans = "";
    while (l1 < n && l2 < m) {
        char it = s1[l1], it2 = s2[l2];
        if (comb == k) {
            ans += it2;
            comb = -1;
            l2++;
        } else if (comb == -k) {
            ans += it;
            comb = 1;
            l1++;
        } else {
            if (it < it2) {
                ans += it;
                if (comb > 0)
                    comb++;
                else
                    comb = 1;
                l1++;
            } else {
                ans += it2;
                if (comb < 0)
                    comb--;
                else
                    comb = -1;
                l2++;
            }
        }
    }
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
}