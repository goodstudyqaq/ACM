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
    long long s, x;
    cin >> n >> s >> x;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    int l = 0;
    long long ans = 0;

    auto work = [&](int l, int r) {
        if (l > r) return 0LL;
        map<long long, int> cnt;
        int nowl = l;
        long long sum2 = 0;
        long long sum = sum2;
        long long res = 0;
        for (int i = nowl; i <= r; i++) {
            sum += a[i];
            long long need = sum - s;
            if (a[i] == x) {
                while (nowl <= i) {
                    cnt[sum2]++;
                    sum2 += a[nowl];
                    nowl++;
                }
            }
            res += cnt[need];
        }
        return res;
    };

    for (int i = 0; i < n; i++) {
        if (a[i] > x) {
            debug(l, i - 1);
            ans += work(l, i - 1);
            l = i + 1;
        }
    }
    debug(l, n - 1);
    ans += work(l, n - 1);
    cout << ans << '\n';
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