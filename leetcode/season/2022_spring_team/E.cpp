#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

#define endl '\n'

struct fast_ios {
    fast_ios() {
        cin.tie(nullptr);
        ios::sync_with_stdio(false);
        cout << fixed << setprecision(10);
    };
} fast_ios_;

class Solution {
   public:
    long long buildBridge(int num, vector<vector<int>>& wood) {
        int n = wood.size();
        vector<long long> len(n);
        vector<long long> l(n);
        for (int i = 0; i < n; i++) {
            len[i] = wood[i][1] - wood[i][0];
            l[i] = wood[i][0];
        }

        priority_queue<long long> ql;
        priority_queue<long long, vector<long long>, greater<long long>> qr;

        ql.push(l[0]);
        qr.push(l[0]);

        long long l_delta = 0, r_delta = 0;

        long long ans = 0;
        for (int i = 1; i < n; i++) {
            l_delta += -len[i];
            r_delta += len[i - 1];

            long long L = ql.top() + l_delta;
            long long R = qr.top() + r_delta;
            if (l[i] >= L && l[i] <= R) {
                ql.push(l[i] - l_delta);
                qr.push(l[i] - r_delta);
            } else if (l[i] < L) {
                ans += L - l[i];
                ql.pop();
                ql.push(l[i] - l_delta);
                ql.push(l[i] - l_delta);
                qr.push(L - r_delta);
            } else {
                ans += l[i] - R;
                qr.pop();
                qr.push(l[i] - r_delta);
                qr.push(l[i] - r_delta);
                ql.push(R - l_delta);
            }
        }
        return ans;
    }
};

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif
    Solution s = Solution();
    int num = 10;
    vector<vector<int>> wood = {{1, 5}, {1, 1}, {10, 10}, {6, 7}, {7, 8}};
    cout << s.buildBridge(num, wood) << endl;
    return 0;
}