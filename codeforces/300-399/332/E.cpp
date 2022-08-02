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
    string p, s;
    int k;
    // cin >> p >> s >> k;
    getline(cin, p);
    getline(cin, s);
    cin >> k;
    int k2 = k;
    debug(s);

    int p_len = p.size();
    int s_len = s.size();
    debug(p_len, s_len);

    if (k > p_len) k = p_len;

    int small = p_len / k;

    int big = small + 1;
    int big_num = p_len % k;
    debug(small, big, big_num);

    if (small > s_len) {
        cout << 0 << endl;
        return 0;
    }
    debug(small);

    auto work = [&](int b_num, int s_num) -> vector<int> {
        vector<int> ans(k2, 0);
        if (b_num) {
            vector<int> res;
            int now = b_num - 1;
            for (int i = big_num - 1; i >= 0 && now >= 0; i--) {
                bool f = true;
                for (int j = i, idx = now; j < p_len; j += k, idx += s_num + b_num) {
                    if (p[j] != s[idx]) {
                        f = false;
                        break;
                    }
                }
                if (f) {
                    res.push_back(i);
                    now--;
                }
            }
            if (now >= 0) return {};
            for (auto it : res) {
                ans[it] = 1;
            }
        }
        if (s_num) {
            vector<int> res2;
            int now = b_num + s_num - 1;
            for (int i = k - 1; i >= big_num && now >= b_num; i--) {
                bool f = true;
                for (int j = i, idx = now; j < p_len; j += k, idx += s_num + b_num) {
                    if (p[j] != s[idx]) {
                        f = false;
                        break;
                    }
                }
                if (f) {
                    res2.push_back(i);
                    now--;
                }
            }

            if (now >= b_num) return {};

            for (auto it : res2) {
                ans[it] = 1;
            }
        }
        return ans;
    };

    vector<int> ans;
    for (int i = 0; i <= big_num; i++) {
        int tmp = i * big;
        if (tmp > s_len) break;
        int tmp2 = s_len - tmp;
        if (tmp2 % small) continue;
        int small_j = tmp2 / small;
        auto res = work(i, small_j);
        debug(res);
        if (res.size()) {
            if (ans.size() == 0) {
                ans = res;
            } else if (ans > res) {
                ans = res;
            }
        }
    }

    if (ans.size() == 0) {
        cout << 0 << endl;
    } else {
        for (auto it : ans) {
            cout << it;
        }
        cout << endl;
    }
    return 0;
}