#include <bits/stdc++.h>

#include "./structure/segment-tree/lazy-segment-tree.hpp"

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

struct Tag {
    // 默认值
    int offset;
    Tag(int offset = 0) : offset(offset) {}
    // apply 之前需要判断 v 是否为默认值
    void apply(const Tag &v, int l, int r) {
        if (v.offset) {
            (offset += v.offset) %= 26;
        }
    }
};

const int inf = 1e9;

struct Info {
    // 默认值
    int min_dis[26], left_idx[26], right_idx[26];
    Info() {
        for (int i = 0; i < 26; i++) {
            left_idx[i] = right_idx[i] = -1;
            min_dis[i] = inf;
        }
    }

    // apply 之前需要判断 v 是否为默认值
    void apply(const Tag &v, int l, int r) {
        if (v.offset) {
            int tmp[26];

            for (int i = 0; i < 26; i++) {
                tmp[(i + v.offset) % 26] = min_dis[i];
            }

            for (int i = 0; i < 26; i++) {
                min_dis[i] = tmp[i];
            }

            for (int i = 0; i < 26; i++) {
                tmp[(i + v.offset) % 26] = left_idx[i];
            }

            for (int i = 0; i < 26; i++) {
                left_idx[i] = tmp[i];
            }

            for (int i = 0; i < 26; i++) {
                tmp[(i + v.offset) % 26] = right_idx[i];
            }

            for (int i = 0; i < 26; i++) {
                right_idx[i] = tmp[i];
            }
        }
    }
    static Info merge(const Info &left_info, const Info &right_info, int l, int r) {
        Info res = Info();

        for (int i = 0; i < 26; i++) {
            res.left_idx[i] = left_info.left_idx[i];
            if (res.left_idx[i] == -1) {
                res.left_idx[i] = right_info.left_idx[i];
            }

            res.right_idx[i] = right_info.right_idx[i];
            if (res.right_idx[i] == -1) {
                res.right_idx[i] = left_info.right_idx[i];
            }

            res.min_dis[i] = min(left_info.min_dis[i], right_info.min_dis[i]);

            if (left_info.right_idx[i] != -1 && right_info.left_idx[i] != -1) {
                res.min_dis[i] = min(res.min_dis[i], right_info.left_idx[i] - left_info.right_idx[i]);
            }
        }
        return res;
    }
};

void solve() {
    int n, m;
    cin >> n >> m;
    string s;
    cin >> s;

    LazySegmentTree<Info, Tag> st(n);
    vector<Info> infos(n);
    for (int i = 0; i < n; i++) {
        infos[i].left_idx[s[i] - 'a'] = i;
        infos[i].right_idx[s[i] - 'a'] = i;
    }
    st.initSegmentTree(infos);

    for (int i = 0; i < m; i++) {
        int t;
        cin >> t;
        if (t == 1) {
            int l, r, x;
            cin >> l >> r >> x;
            l--, r--;
            st.rangeUpdate(l, r + 1, Tag(x));
        } else {
            int l, r;
            cin >> l >> r;
            l--, r--;
            auto it = st.rangeQuery(l, r + 1);
            bool ok = true;
            for (int i = 0; i < 26; i++) {
                if (it.min_dis[i] <= 2) {
                    ok = false;
                    break;
                } 
            }
            if (ok) {
                cout << "YES\n";
            } else {
                cout << "NO\n";
            }
        }
    }
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