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
    vector<long long> a(n + 1);
    map<long long, int> cnt;
    long long mx = 0;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        cnt[a[i]]++;
        mx = max(mx, a[i]);
    }

    long long K = 1e6;
    long long ans = 0;

    for (auto it : cnt) {
        long long val = it.first;
        long long num = it.second;

        if (num >= 3) {
            ans += (num * (num - 1) * (num - 2));
        }

        if (val <= K) {
            for (int i = 1; i * i <= val; i++) {
                if (val % i == 0) {
                    int b = i;
                    if (b != 1) {
                        int ai = val / b;
                        long long ak = val * b;
                        if (cnt.count(ai) && cnt.count(ak)) {
                            ans += num * cnt[ai] * cnt[ak];
                        }
                    }
                    if (i * i != val) {
                        b = val / i;
                        int ai = val / b;
                        long long ak = val * b;
                        if (cnt.count(ai) && cnt.count(ak)) {
                            ans += num * cnt[ai] * cnt[ak];
                        }
                    }
                }
            }
        } else {
            // 复杂度 1000 * 1000
            for (long long b = 2; b * val <= mx; b++) {
                if (val % b == 0 && cnt.count(b * val) && cnt.count(val / b)) {
                    ans += (num * cnt[b * val] * cnt[val / b]);
                }
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
    return 0;
}