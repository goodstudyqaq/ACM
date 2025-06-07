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

    int n;
    cin >> n;
    vector<int> p(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> p[i];
    }

    vector<int> idx1, idx2;
    for (int i = 2; i < n; i++) {
        if (p[i] > p[i - 1] && p[i] > p[i + 1]) {
            idx1.push_back(i);
        }
        if (p[i] < p[i - 1] && p[i] < p[i + 1]) {
            idx2.push_back(i);
        }
    }

    int r1 = 0, r2 = 0;
    long long ans = 0;
    debug(idx1, idx2);
    for (int i = 1; i < n; i++) {
        if (p[i] < p[i + 1]) {
            while (r1 < idx1.size() && idx1[r1] <= i) {
                r1++;
            }
            while (r2 < idx2.size() && idx2[r2] <= i) {
                r2++;
            }

            if (r1 < idx1.size() && r2 < idx2.size()) {
                int tmp1 = idx1[r1], tmp2 = idx2[r2];
                bool only_one = true;
                if (tmp1 < tmp2) {
                    if (r1 + 1 < idx1.size() && idx1[r1 + 1] < tmp2) {
                        only_one = false;
                    }
                } else {
                    if (r2 + 1 < idx2.size() && idx2[r2 + 1] < tmp1) {
                        only_one = false;
                    }
                }
                if (only_one) {
                    int min_loc = n;
                    if (r1 + 1 < idx1.size()) {
                        min_loc = min(min_loc, idx1[r1 + 1]);
                    }
                    if (r2 + 1 < idx2.size()) {
                        min_loc = min(min_loc, idx2[r2 + 1]);
                    }
                    debug(i, min_loc, max(tmp1, tmp2));
                    ans += min_loc - max(tmp1, tmp2);
                }
            }
        }
    }
    cout << ans << '\n';
}