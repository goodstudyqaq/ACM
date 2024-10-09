#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

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
    vector<int> p(n + 1), pos(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> p[i];
        pos[p[i]] = i;
    }
    vector<int> l(n + 2), r(n + 2);
    for (int i = 0; i <= n + 1; i++) {
        l[i] = max(0, i - 1);
        r[i] = min(n + 1, i + 1);
    }

    long long ans = 0;

    for (int i = 1; i <= n; i++) {
        int _pos = pos[i];
        int now = l[_pos];

        vector<int> Left, Right;
        while (Left.size() < k) {
            Left.push_back(now);
            now = l[now];
        }

        now = r[_pos];
        while (Right.size() < k) {
            Right.push_back(now);
            now = r[now];
        }
        debug(i, Left, Right);

        long long num = 0;
        for (int j = 0; j < Left.size(); j++) {
            int last = (j == 0 ? _pos : Left[j - 1]);
            int j2 = k - j - 1;
            if (j2 < Right.size()) {
                long long tmp = 1LL * (last - Left[j]) * (Right[j2] - (j2 - 1 >= 0 ? Right[j2 - 1] : _pos));
                debug(j, tmp);
                num += tmp;
            }
        }
        ans += num * i;
        r[l[_pos]] = r[_pos];
        l[r[_pos]] = l[_pos];
    }
    cout << ans << endl;
}