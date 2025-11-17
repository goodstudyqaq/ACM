#include <bits/stdc++.h>

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
    int left_bracket, right_bracket;
    Info(int left_bracket = 0, int right_bracket = 0) : left_bracket(left_bracket), right_bracket(right_bracket) {}
    static Info merge(const Info& left_info, const Info& right_info, int l, int r) {
        int ans1 = left_info.left_bracket + right_info.left_bracket - min(left_info.left_bracket, right_info.right_bracket);
        int ans2 = left_info.right_bracket + right_info.right_bracket - min(left_info.left_bracket, right_info.right_bracket);
        return Info(ans1, ans2);
    }
    string to_string() {
        return "";
    }
};

void solve() {
    string s;
    cin >> s;

    int q;
    cin >> q;
    int n = s.size();
    vector<Info> infos(n);
    for (int i = 0; i < n; i++) {
        if (s[i] == '(') {
            infos[i] = Info(1, 0);
        } else {
            infos[i] = Info(0, 1);
        }
    }

    SegmentTree<Info> seg(infos);

    while (q--) {
        int l, r;
        cin >> l >> r;
        l--, r--;
        int len = r - l + 1;
        auto it = seg.rangeQuery(l, r + 1);
        cout << len - it.left_bracket - it.right_bracket << '\n';
    }
}

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif

    int T = 1;
    while (T--) {
        solve();
    }
    return 0;
}