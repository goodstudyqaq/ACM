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
    int n, k, pb, ps;
    cin >> n >> k >> pb >> ps;
    vector<int> p(n + 1), a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> p[i];
    }
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    auto work = [&](int start) -> long long {
        int step = min(n, k);

        long long before = 0;
        long long ans = 0;
        int now = 0;
        int now_idx = start;
        while (now < step) {
            long long res = before + 1LL * (k - now) * a[now_idx];
            ans = max(ans, res);
            before += a[now_idx];
            now++;
            now_idx = p[now_idx];
        }
        return ans;
    };

    long long score_pb = work(pb);
    long long score_ps = work(ps);

    if (score_pb > score_ps) {
        cout << "Bodya" << endl;
    } else if (score_pb < score_ps) {
        cout << "Sasha" << endl;
    } else {
        cout << "Draw" << endl;
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