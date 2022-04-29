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
    vector<int> t(n + 1), y(n + 1);
    vector<int> IDX;
    for (int i = 1; i <= n; i++) {
        cin >> t[i] >> y[i];
        if (t[i] == 1) {
            IDX.push_back(i);
        }
    }
    long long ans = -numeric_limits<long long>::max() / 2;
    multiset<int> S;
    int now_ct = 0;
    long long now_val = 0;
    int i;
    for (i = n; i >= 1; i--) {
        if (t[i] == 1) {
            long long val = y[i];
            ans = max(ans, val + now_val);
            now_ct++;
            if (S.size() + now_ct > k) {
                if (S.size()) {
                    auto it = prev(S.end());
                    long long the_val = *it;
                    S.erase(it);
                    now_val += the_val;
                } else {
                    break;
                }
            }
        } else {
            if (y[i] < 0) {
                if (S.size() + now_ct < k) {
                    S.insert(y[i]);
                } else {
                    if (S.size()) {
                        auto it = prev(S.end());
                        if (*it > y[i]) {
                            long long val = *it;
                            S.erase(it);
                            S.insert(y[i]);
                            now_val += val;
                        } else {
                            now_val += y[i];
                        }
                    } else {
                        now_val += y[i];
                    }
                }
            } else {
                now_val += y[i];
            }
        }
    }
    debug(now_val, i);
    if (i == 0) {
        ans = max(ans, now_val);
    }
    cout << ans << endl;
    return 0;
}