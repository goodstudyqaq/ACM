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

// struct fast_ios {
//     fast_ios() {
//         cin.tie(nullptr);
//         ios::sync_with_stdio(false);
//         cout << fixed << setprecision(10);
//     };
// } fast_ios_;

void solve() {
    int n;
    cin >> n;
    auto ask = [&](int idx, int loc) {
        cout << "? " << idx << ' ' << (1 << loc) << '\n';
        fflush(stdout);
        int res;
        cin >> res;
        return res;
    };

    auto out = [&](int ans) {
        cout << "! " << ans << '\n';
        fflush(stdout);
    };

    const int M = 15;
    vector<vector<int>> cnt(M, vector<int>(2));
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < M; j++) {
            int val = (i >> j) & 1;
            cnt[j][val]++;
        }
    }
    set<int> S;

    vector<int> loc;
    for (int i = 1; i <= n; i++) {
        S.insert(i);
        loc.push_back(i);
    }
    int ans = 0;
    int cnt_zero = cnt[0][0], cnt_one = cnt[0][1];
    for (int i = 0; i < M; i++) {
        int idx = 0;
        map<int, int> tmp_res;
        while (cnt_zero && cnt_one) {
            int tmp = ask(loc[idx], i);
            tmp_res[loc[idx]] = tmp;
            if (tmp == 0) {
                cnt_zero--;
            } else {
                cnt_one--;
            }
            idx++;
        }
        debug(i, cnt_zero, cnt_one);
        vector<int> new_loc;
        set<int> new_S;
        if (cnt_zero == 0) {
            ans += (1 << i);
            //
            for (auto it : loc) {
                if (tmp_res.count(it) == 0) {
                    new_loc.push_back(it);
                } else {
                    if (tmp_res[it] == 1) {
                        new_loc.push_back(it);
                    }
                }
            }
            for (auto it : S) {
                if (((it >> i) & 1) == 1) {
                    new_S.insert(it);
                }
            }

        } else {
            for (auto it : loc) {
                if (tmp_res.count(it) == 0) {
                    new_loc.push_back(it);
                } else {
                    if (tmp_res[it] == 0) {
                        new_loc.push_back(it);
                    }
                }
            }
            for (auto it : S) {
                if (((it >> i) & 1) == 0) {
                    new_S.insert(it);
                }
            }
        }
        loc = new_loc;
        S = new_S;
        debug(S);
        cnt_one = 0, cnt_zero = 0;
        for (auto it : S) {
            if (((it >> (i + 1)) & 1) == 0) {
                cnt_zero++;
            } else {
                cnt_one++;
            }
        }
        debug(cnt_one, cnt_zero);
    }
    out(ans);
}

int main() {
    // #ifdef LOCAL
    //     freopen("./data.in", "r", stdin);
    // #endif

    int T;
    cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}