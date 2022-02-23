// copy_start_symbol=hello copy_end_symbol=world
#include "../../header.h"
//hello
const int maxn = 305;
const int inf = 0x3f3f3f3f;
#define map mp
int nL, nR;
int map[maxn][maxn];  //二分图描述
int cx[maxn], cy[maxn];
int dx[maxn], dy[maxn];
int lx[maxn], ly[maxn];
bool find(int u) {
    dx[u] = 1;
    for (int i = 1; i <= nR; i++)
        if (!dy[i] && lx[u] + ly[i] == map[u][i]) {
            dy[i] = 1;
            if (cy[i] == -1 || find(cy[i])) {
                cx[u] = i;
                cy[i] = u;
                return 1;
            }
        }
    return 0;
}
int KM() {
    memset(cx, -1, sizeof(cx));
    memset(cy, -1, sizeof(cy));
    memset(ly, 0, sizeof(ly));
    for (int i = 1; i <= nL; i++) {
        lx[i] = 0;
        for (int j = 1; j <= nR; j++)
            lx[i] = max(lx[i], map[i][j]);
    }
    for (int u = 1; u <= nL; u++) {
        while (1) {
            memset(dx, 0, sizeof(dx));
            memset(dy, 0, sizeof(dy));
            if (find(u)) break;
            int inc = inf;
            for (int i = 1; i <= nL; i++)
                if (dx[i])
                    for (int j = 1; j <= nR; j++)
                        if (!dy[j])
                            inc = min(inc, lx[i] + ly[j] - map[i][j]);
            for (int i = 1; i <= nL; i++)
                if (dx[i]) lx[i] -= inc;
            for (int i = 1; i <= nR; i++)
                if (dy[i]) ly[i] += inc;
        }
    }
    int ans = 0;
    for (int i = 1; i <= nL; i++)
        if (cx[i] != -1)
            ans += map[i][cx[i]];
    return ans;
}

class Solution {
   public:
    vector<int> sum;
    int maximumANDSum(vector<int>& nums, int slo) {
        int n = nums.size();
        // 左边有 n 个点 右边有 slo * 2 个点
        nL = n;
        nR = slo * 2;
        for (int i = 0; i < n; i++) {
            for (int j = 1; j <= slo; j++) {
                map[i + 1][j * 2 - 1] = nums[i] & j;
                map[i + 1][j * 2] = nums[i] & j;
            }
        }
        return KM();
    }
};
//world