#include <bits/stdc++.h>

#include <queue>

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

    int n, m;
    cin >> n >> m;
    vector<long long> a(n + 1), b(n + 1), c(m + 1);
    int maxn = 1e6;
    vector<long long> have(maxn + 1, 1e9);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = 1; i <= n; i++) {
        cin >> b[i];
    }

    for (int i = 1; i <= n; i++) {
        int tmp = a[i] - b[i];
        have[tmp] = min(have[tmp], a[i]);
    }
    int now = 1;
    int last = -1;
    vector<int> valid_idx;
    while (now <= maxn) {
        int go = now;
        while (go <= maxn && have[go] == 1e9) {
            go++;
        }
        if (go > maxn) break;
        if (last == -1 || last > have[go]) {
            valid_idx.push_back(go);
            last = have[go];
        }
        now = go + 1;
    }
    debug(valid_idx);

    map<long long, int> M;

    for (int i = 1; i <= m; i++) {
        cin >> c[i];
        M[-c[i]]++;
    }
    long long ans = 0;

    for (auto it : valid_idx) {
        int the_have = have[it];
        while (true) {
            auto it2 = -M.begin()->first;
            // debug(the_have, it2);
            if (the_have > it2) {
                break;
            }
            int times = M[-it2];
            M.erase(-it2);

            long long tmp = (it2 - the_have) / it + 1;
            ans += tmp * times * 2;
            it2 -= tmp * it;

            M[-it2] += times;

        }
    }
    cout << ans << endl;
}