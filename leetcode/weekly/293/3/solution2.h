#include <bits/stdc++.h>
using namespace std;
class CountIntervals {
    CountIntervals *left = nullptr, *right = nullptr;
    int l, r, cnt;

   public:
    CountIntervals(int _l, int _r) : l(_l), r(_r) {
        cnt = 0;
    }
    CountIntervals() {
        l = 1, r = 1e9;
        cnt = 0;
    }

    void add(int L, int R) {
        if (r - l + 1 == cnt) return;
        if (L <= l && r <= R) {
            cnt = r - l + 1;
            return;
        }
        int mid = l + r >> 1;
        if (L <= mid) {
            if (left == nullptr) {
                left = new CountIntervals(l, mid);
            }
            left->add(L, R);
        }
        if (R > mid) {
            if (right == nullptr) {
                right = new CountIntervals(mid + 1, r);
            }
            right->add(L, R);
        }
        cnt = 0;
        if (left != nullptr) cnt += left->cnt;
        if (right != nullptr) cnt += right->cnt;
    }

    int count() {
        return cnt;
    }
};
