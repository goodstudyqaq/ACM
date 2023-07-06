#if __has_include("../../utils/cpp/help.hpp")
#include "../../utils/cpp/help.hpp"
#endif

#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
template <class Info, class Merge = std::plus<Info>>
struct SegmentTree {
    SegmentTree(int n) : n(n), merge(Merge()), info(4 << __lg(n)) {}
    SegmentTree(vector<Info> init) : SegmentTree(init.size()) {
        function<void(int, int, int)> build = [&](int l, int r, int rt) {
            if (l == r) {
                info[rt] = init[l];
                return;
            }
            int m = l + r >> 1;
            build(lson);
            build(rson);
            push_up(rt);
        };
        build(0, n - 1, 1);
    }

    Info rangeQuery(int l, int r) {
        return rangeQuery(l, r, 0, n - 1, 1);
    }

    void update(int L, Info v) {
        return update(L, v, 0, n - 1, 1);
    }

   private:
    const int n;
    const Merge merge;
    vector<Info> info;
    void push_up(int rt) {
        info[rt] = merge(info[rt << 1], info[rt << 1 | 1]);
    }

    Info rangeQuery(int L, int R, int l, int r, int rt) {
        if (L <= l && r <= R) {
            return info[rt];
        }
        int m = l + r >> 1;
        if (L <= m && R > m) {
            return merge(rangeQuery(L, R, lson), rangeQuery(L, R, rson));
        } else if (L <= m) {
            return rangeQuery(L, R, lson);
        } else {
            return rangeQuery(L, R, rson);
        }
    }

    void update(int L, Info& v, int l, int r, int rt) {
        if (l == r) {
            info[rt] = merge(info[rt], v);
            return;
        }
        int m = l + r >> 1;
        if (L <= m) {
            update(L, v, lson);
        } else {
            update(L, v, rson);
        }
        push_up(rt);
    }
};

struct Info {
    int v;
    Info(int x = 0) {
        v = x;
    }
};

Info operator+(const Info& a, const Info& b) {
    Info c;
    c.v = max(a.v, b.v);
    return c;
}

class Solution {
   public:
    int lengthOfLIS(vector<int>& nums, int k) {
        int n = nums.size();
        const int m = 1e5 + 1;
        SegmentTree<Info> seg(m);
        int ans = 0;
        for (int i = 0; i < n; i++) {
            int val = nums[i];
            int l = max(1, val - k);
            int r = val - 1;
            // [l, r]
            Info res;
            if (val == 1) {
                res.v = 0;
            } else {
                res = seg.rangeQuery(l, r);
            }
            res.v++;
            ans = max(ans, res.v);
            seg.update(val, res);
        }
        return ans;
    }
};