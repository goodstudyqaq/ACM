#include <bits/stdc++.h>

#include <algorithm>
#include <cassert>

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
    cin >> n;
    vector<int> a(n);
    set<int> S;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        S.insert(a[i]);
    }

    map<int, int> suf_cnt;
    int now = n - 1;
    while (suf_cnt.size() < S.size()) {
        suf_cnt[a[now]]++;
        now--;
    }
    now++;

    set<pii> pre_val;
    for (int i = 0; i <= now; i++) {
        pre_val.insert({a[i], i});
    }

    vector<int> res;
    set<int> vis;
    // debug(now);

    int last_choose = -1;
    for (int i = 1; i <= S.size(); i++) {
        int val;
        // debug(i, now, pre_val, res, vis, suf_cnt);
        if (i % 2) {
            // 选最大的
            while (true) {
                auto it = prev(pre_val.end());
                if (vis.count(it->first)) {
                    pre_val.erase(it);
                } else if (it->second < last_choose) {
                    pre_val.erase(it);
                } else {
                    val = it->first;

                    while (it != pre_val.begin() && prev(it)->first == val && prev(it)->second > last_choose) {
                        it--;
                    }

                    res.push_back(-val);
                    vis.insert(val);
                    last_choose = it->second;
                    break;
                }
            }
        } else {
            // 选最小的
            while (true) {
                auto it = *pre_val.begin();
                if (vis.count(it.first)) {
                    pre_val.erase(it);
                } else if (it.second < last_choose) {
                    pre_val.erase(it);
                } else {
                    val = it.first;
                    res.push_back(val);
                    vis.insert(val);
                    last_choose = it.second;
                    break;
                }
            }
        }

        while (now < n) {
            if (vis.count(a[now])) {
                now++;
            } else {
                if (suf_cnt[a[now]] > 1) {
                    suf_cnt[a[now]]--;
                    pre_val.insert({a[now], now});
                    now++;
                } else {
                    assert(suf_cnt[a[now]] == 1);
                    pre_val.insert({a[now], now});
                    break;
                }
            }
        }
    }

    cout << res.size() << endl;
    for (auto it : res) {
        cout << abs(it) << ' ';
    }
    cout << endl;
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