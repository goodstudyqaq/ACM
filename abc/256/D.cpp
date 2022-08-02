#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

#define endl '\n'
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

class CountIntervals {
    typedef pair<int, int> pii;

   public:
    int ans = 0;
    set<pii> S;
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

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif
    int n;
    cin >> n;
    CountIntervals sol;
    for (int i = 0; i < n; i++) {
        int l, r;
        cin >> l >> r;
        sol.add(l, r - 1);
    }

    for (auto it : sol.S) {
        cout << it.first << ' ' << it.second + 1 << endl;
    }
    return 0;
}