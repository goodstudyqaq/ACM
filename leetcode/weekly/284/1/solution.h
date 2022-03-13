/*
Code generated by https://github.com/goodStudyTnT/leetcode-tester
*/

#if __has_include("../../utils/cpp/help.h")
#include "../../utils/cpp/help.h"
#endif

class Solution {
   public:
    vector<vector<bool>> vis;
    int digArtifacts(int n, vector<vector<int>>& artifacts, vector<vector<int>>& dig) {
        vis.resize(n, vector<bool>(n));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                vis[i][j] = 0;
            }
        }
        int m = dig.size();
        for (int i = 0; i < m; i++) {
            int x = dig[i][0], y = dig[i][1];
            vis[x][y] = 1;
        }
        int res = 0;
        m = artifacts.size();
        for (int i = 0; i < m; i++) {
            int sz = artifacts[i].size();
            bool f = true;
            int x1 = artifacts[i][0], y1 = artifacts[i][1], x2 = artifacts[i][2], y2 = artifacts[i][3];
            for (int x = x1; x <= x2; x++) {
                for (int y = y1; y <= y2; y++) {
                    if (vis[x][y] == 0) {
                        f = false;
                        x = x2 + 1;
                        break;
                    }
                }
            }
            if (f) {
                res++;
            }
        }
        return res;
    }
};