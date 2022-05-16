// set 常见使用套路
// 维护区间
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
        auto it = S.upper_bound({left - 1, -1});
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
};
