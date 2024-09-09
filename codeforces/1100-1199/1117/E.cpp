#include <bits/stdc++.h>

#include <cassert>
#include <cstdio>
#include <numeric>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

// struct fast_ios {
//     fast_ios() {
//         cin.tie(nullptr);
//         ios::sync_with_stdio(false);
//         cout << fixed << setprecision(10);
//     };
// } fast_ios_;

int main() {
    // #ifdef LOCAL
    //     freopen("./data.in", "r", stdin);
    // #endif
    string s;
    cin >> s;

    int n = s.size();
    vector<string> q(3), res(3);
    for (int i = 0; i < 3; i++) {
        q[i].resize(n);
    }

    vector<int> V(n);
    iota(V.begin(), V.end(), 0);

    function<void(vector<int> &, int)> work = [&](vector<int> &V, int _idx) {
        debug(V, _idx);
        if (_idx == 3) return;
        int now = 0;
        vector<vector<int>> idxs(26);
        for (auto it : V) {
            q[_idx][it] = now + 'a';
            idxs[now].push_back(it);
            now = (now + 1) % 26;
        }

        for (int i = 0; i < 26; i++) {
            work(idxs[i], _idx + 1);
        }
    };

    auto query = [&](string &q) {
        cout << "? " << q << endl;
        fflush(stdout);
        string res;
        cin >> res;
        return res;
    };

    work(V, 0);
    debug(q);
    for (int i = 0; i < 3; i++) {
        res[i] = query(q[i]);
    }

    vector<int> p(n);

    vector<int> left(n), right(n);
    iota(left.begin(), left.end(), 0);
    iota(right.begin(), right.end(), 0);

    function<void(vector<int> & left, vector<int> & right, int _idx)> deal = [&](vector<int> &left, vector<int> &right, int _idx) {
        if (left.size() == 1) {
            p[left[0]] = right[0];
            return;
        }
        vector<vector<int>> left_idx(26), right_idx(26);
        for (auto it : left) {
            left_idx[q[_idx][it] - 'a'].push_back(it);
        }
        for (auto it : right) {
            right_idx[res[_idx][it] - 'a'].push_back(it);
        }
        for (int i = 0; i < 26; i++) {
            if (left_idx[i].size()) {
                deal(left_idx[i], right_idx[i], _idx + 1);
            }
        }
    };
    deal(left, right, 0);

    string ans(n, ' ');
    for (int i = 0; i < n; i++) {
        int idx = p[i];
        ans[i] = s[idx];
    }
    cout << "! " << ans << endl;
    fflush(stdout);
    return 0;
}