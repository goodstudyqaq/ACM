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
    int perfectMenu(vector<int>& materials, vector<vector<int>>& cookbooks, vector<vector<int>>& attribute, int limit) {
        int n = cookbooks.size();
        int LIMIT = 1 << n;
        int res = -1;

        auto check = [&](int s) -> int {
            vector<int> mat = materials;
            int a = 0, b = 0;
            for (int i = 0; i < n; i++) {
                if ((s >> i) & 1) {
                    for (int j = 0; j < 5; j++) {
                        mat[j] -= cookbooks[i][j];
                        if (mat[j] < 0) return -1;
                    }
                    a += attribute[i][0], b += attribute[i][1];
                }
            }
            if (b >= limit) {
                return a;
            } else {
                return -1;
            }
        };

        for (int i = 1; i < LIMIT; i++) {
            int tmp = check(i);
            if (tmp != -1) {
                res = max(res, tmp);
            }
        }
        return res;
    }
};
int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif
}