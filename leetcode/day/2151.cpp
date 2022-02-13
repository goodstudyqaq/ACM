// copy_start_symbol=hello copy_end_symbol=world
#include "../header.h"

// hello
class Solution {
   public:
    int n;
    vector<vector<int>>& sta;
    int check(int status) {
        vector<int> num;
        int s2 = status;
        int res = 0;
        for (int i = 0; i < n; i++) {
            if ((status >> i) & 1) {
                res++;
                for (int j = 0; j < n; j++) {
                    if (sta[i][j] == 1) {
                        if (((status >> j) & 1) == 0) return -1;
                    } else if (sta[i][j] == 0) {
                        if ((status >> j) & 1) return -1;
                    }
                }
            }
        }

        return res;
    }

    int maximumGood(vector<vector<int>>& statements) {
        n = statements.size();
        sta = statements;
        int LIMIT = 1 << n;
        int res = 0;
        for (int i = 0; i < LIMIT; i++) {
            int tmp = check(i);
            if (tmp != -1) {
                res = max(res, tmp);
            }
        }
        return res;
    }
};
// world