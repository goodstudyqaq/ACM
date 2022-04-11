#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

#define endl '\n'

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
    int n, k;
    cin >> n >> k;
    vector<long long> b;
    b.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> b[i];
    }

    vector<long long> times, score;
    times.resize(n + 1);
    score.resize(n + 1);
    long long now_times = 0, now_score = 0;
    long long ans = 0;
    for (int i = n; i >= 1; i--) {
        now_times += times[i];
        now_score += score[i];

        b[i] += now_times * i + now_score;

        if (b[i] > 0) {
            long long v = min(i, k);
            long long tmpt = (b[i] - 1) / v + 1;

            ans += tmpt;

            now_times -= tmpt;
            now_score -= tmpt * (v - i);

            if (i - k >= 1) {
                times[i - k] += tmpt;
                score[i - k] += tmpt * (v - i);
            }
        }
    }
    cout << ans << endl;
    return 0;
}