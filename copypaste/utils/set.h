// set 常见使用套路
// 维护区间
/* 
现在模板的逻辑：[l, r], [r+1, r2] => [l, r2], 如果想改成 [l, r], [r, r2] => [l, r2] 可以自己变通
https://atcoder.jp/contests/abc254/tasks/abc254_g
https://leetcode.com/problems/count-integers-in-intervals/
https://atcoder.jp/contests/abc256/tasks/abc256_h
*/
#include <bits/stdc++.h>
using namespace std;
class CountIntervals {
    typedef pair<int, int> pii;

    int ans = 0;
    set<pii> S;

   public:
    CountIntervals() {
        ans = 0;
        S.clear();
    }

    void add(int left, int right) {
        auto it = S.lower_bound({left, -1});  // 目的是想找到第一个包围 [left - 1, right + 1] 的区间。
        if (it != S.begin()) {
            if (prev(it)->second >= left - 1) {
                it--;
            }
        }

        int L = left, R = right;
        while (it != S.end()) {
            if (it->first > right + 1) break;
            L = min(L, it->first);
            R = max(R, it->second);
            ans -= it->second - it->first + 1;
            it = S.erase(it);
        }
        ans += R - L + 1;
        S.insert({L, R});
    }

    int count() {
        return ans;
    }

    pii get_interval(int idx) {
        auto it = S.lower_bound({idx + 1, -1});  // 写法很关键，找最后一个包围 idx 的区间可以这么写
        if (it == S.begin()) {
            return {-1, -1};
        }
        it--;
        if (it->second < idx) {
            return {-1, -1};
        }
        return *it;
    }
};
