#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

#define endl '\n'
typedef long long ll;

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
    map<int, int> M;
    vector<int> a_left, a_right;
    map<int, int> Left, Right;
    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        if (i < n / 2) {
            a_left.push_back(a);
            Left[a]++;
        } else {
            a_right.push_back(a);
            Right[a]++;
        }
        M[a]++;
    }
    if (n % 2) {
        cout << -1 << endl;
        return;
    }

    for (auto it : M) {
        if (it.second % 2) {
            cout << -1 << endl;
            return;
        }
    }
    typedef pair<int, int> pii;
    vector<pii> push;
    for (auto it : M) {
        int val = it.first;
        int left_cnt = Left[val];
        int right_cnt = Right[val];
        if (left_cnt == right_cnt) continue;
        if (left_cnt < right_cnt) {
            int tmp = (right_cnt - left_cnt) / 2;
            while (tmp--) {
                push.push_back({val, 0});
            }
        } else {
            int tmp = (left_cnt - right_cnt) / 2;
            while (tmp--) {
                push.push_back({val, -1});
            }
        }
    }
    // cout << push.size() << endl;
    int now_sz = n;
    vector<pii> real_push;

    for (int i = 0; i < push.size(); i++) {
        int val = push[i].first, flag = push[i].second;
        if (flag == 0) {
            int sz = a_left.size();
            real_push.push_back({sz, val});
            // cout << sz << ' ' << val << endl;
            a_left.push_back(val);
            a_left.push_back(val);
        } else {
            int sz = a_right.size() + a_left.size();
            real_push.push_back({sz, val});
            // cout << sz << ' ' << val << endl;
            a_right.push_back(val);
            a_right.push_back(val);
        }
    }
    debug(a_left, a_right);
    vector<pii> ans;

    auto convert = [&](vector<int> &v, int num, int offset) {
        ans.push_back({offset, offset + num + num});
        vector<int> res;
        for (int i = 0; i < num; i++) {
            real_push.push_back({offset + num + i, v[i]});
        }
        for (int i = num - 1; i >= 0; i--) {
            res.push_back(v[i]);
        }
        for (int i = num; i < v.size(); i++) {
            res.push_back(v[i]);
        }
        return res;
    };

    int now_idx = a_right.size() - 1;
    int offset = 0;
    while (now_idx >= 0) {
        if (now_idx == 0) {
            ans.push_back({offset, offset + a_left.size() * 2});
            break;
        }
        int val = a_right[now_idx];
        int choose;
        for (int i = 0; i < a_left.size(); i++) {
            if (a_left[i] == val) {
                choose = i;
                break;
            }
        }
        debug(now_idx, a_left, ans);
        if (choose != 0) {
            a_left = convert(a_left, choose + 1, offset);
            offset += 2 * (choose + 1);
        }
        debug(now_idx, a_left, ans);
        int sz = a_left.size();
        a_left = convert(a_left, now_idx + 1, offset);
        offset += 2 * (now_idx + 1);
        now_idx--;
        debug(now_idx, a_left, ans);
    }
    debug(a_left);
    debug(a_right);

    cout << real_push.size() << endl;
    for (auto it : real_push) {
        cout << it.first << ' ' << it.second << endl;
    }
    cout << ans.size() << endl;
    debug(ans);
    for (auto it : ans) {
        // debug(it);
        cout << it.second - it.first << ' ';
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
}