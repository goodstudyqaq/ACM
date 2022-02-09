// copy_start_symbol=hello copy_end_symbol=world
#include "../header.h"

// hello

int d[5][2] = {1, 0, -1, 0, 0, 1, 0, -1, 0, 0};
class Solution {
   public:
    int n, m;
    bool check(vector<vector<int>>& mat) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (mat[i][j] == 1) return 0;
            }
        }
        return 1;
    }

    int minFlips(vector<vector<int>>& mat) {
        n = mat.size();
        m = mat[0].size();
        int all = n * m;
        int LIMIT = 1 << all;

        int res = 1e9;
        for (int i = 0; i < LIMIT; i++) {
            auto it = mat;
            int num = 0;
            for (int j = 0; j < all; j++) {
                if ((i >> j) & 1) {
                    num++;
                    int row = j / m;
                    int col = j % m;
                    for (int k = 0; k < 5; k++) {
                        int tmpx = row + d[k][0];
                        int tmpy = col + d[k][1];
                        if (tmpx >= 0 && tmpx < n && tmpy >= 0 && tmpy < m) {
                            it[tmpx][tmpy] ^= 1;
                        }
                    }
                }
            }

            if (check(it)) {
                res = min(res, num);
            }
        }
        if (res == 1e9) res = -1;
        return res;
    }
};
// world