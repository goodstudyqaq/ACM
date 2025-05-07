#include <bits/stdc++.h>

#include <algorithm>

#include "structure/segment-tree/segment-tree.hpp"

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

struct Info {
    // 默认值
    int valid_num, left_close, right_open;
    Info(int valid_num = 0, int left_close = 0, int right_open = 0) : valid_num(valid_num), left_close(left_close), right_open(right_open) {
    }
    static Info merge(const Info& left_info, const Info& right_info, int l, int r) {
        int ct = min(left_info.right_open, right_info.left_close);
        int valid_num = left_info.valid_num + right_info.valid_num + ct * 2;
        int left_close = left_info.left_close + right_info.left_close - ct;
        int right_open = right_info.right_open + left_info.right_open - ct;
        return Info{valid_num, left_close, right_open};
    }
    string to_string() {
        return "";
    }
};

void solve() {
    string s;
    cin >> s;
    int n = s.size();

    vector<Info> infos(n);
    for (int i = 0; i < n; i++) {
        if (s[i] == '(') {
            infos[i].right_open = 1;
        } else {
            infos[i].left_close = 1;
        }
    }
    SegmentTree<Info> seg(infos);

    int m;
    cin >> m;
    while (m--) {
        int l, r;
        cin >> l >> r;
        l--, r--;
        cout << seg.rangeQuery(l, r + 1).valid_num << '\n';
    }
}

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif

    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}