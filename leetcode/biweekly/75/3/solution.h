/*
Code generated by https://github.com/goodStudyTnT/leetcode-tester
*/

#if __has_include("../../utils/cpp/help.h")
#include "../../utils/cpp/help.h"
#endif
//SA[i]=a 排名为i的下标为a
//rank[a]=i 下标为a的排名为i
//height[i]=a 排名为i的和排名为i-1是最长公共前缀
//下标从1到N 千万不能搞错
#define rank rk
const int maxn = 20005;
int ch[maxn];
int cntA[maxn], cntB[maxn], A[maxn], B[maxn], tsa[maxn], SA[maxn], rank[maxn], height[maxn];
int N;
void get_SA() {
    for (int i = 0; i <= 200; i++) cntA[i] = 0;
    for (int i = 1; i <= N; i++) cntA[ch[i]]++;
    for (int i = 1; i <= 200; i++) cntA[i] += cntA[i - 1];
    for (int i = N; i >= 1; i--) SA[cntA[ch[i]]--] = i;
    rank[SA[1]] = 1;
    for (int i = 2; i <= N; i++) {
        rank[SA[i]] = rank[SA[i - 1]];
        if (ch[SA[i]] != ch[SA[i - 1]])
            rank[SA[i]]++;
    }
    for (int step = 1; rank[SA[N]] < N; step <<= 1) {
        for (int i = 1; i <= N; i++) cntA[i] = cntB[i] = 0;
        for (int i = 1; i <= N; i++) {
            cntA[A[i] = rank[i]]++;
            cntB[B[i] = (i + step <= N) ? rank[i + step] : 0]++;
        }
        for (int i = 1; i <= N; i++) cntA[i] += cntA[i - 1], cntB[i] += cntB[i - 1];
        for (int i = N; i >= 1; i--) tsa[cntB[B[i]]--] = i;
        for (int i = N; i >= 1; i--) SA[cntA[A[tsa[i]]]--] = tsa[i];
        rank[SA[1]] = 1;
        for (int i = 2; i <= N; i++) {
            rank[SA[i]] = rank[SA[i - 1]];
            if (A[SA[i]] != A[SA[i - 1]] || B[SA[i]] != B[SA[i - 1]])
                rank[SA[i]]++;
        }
    }
}
void get_Height() {
    int i, j, k = 0;
    for (int i = 1; i <= N; i++) {
        if (k) k--;
        j = SA[rank[i] - 1];
        while (ch[i + k] == ch[j + k]) k++;
        height[rank[i]] = k;
    }
}

class Solution {
   public:
    long long sumScores(string s) {
        int m = s.size();
        for (int i = 0; i < m; i++) {
            ch[i + 1] = s[i];
        }
        ch[] N = m;
        get_SA();
        get_Height();

        int rk_1 = rk[1];
        long long ans = 0;
        int val = height[rk_1];
        int now = rk_1;
        while (now >= 2) {
            debug(val);
            ans += val;
            now--;
            val = min(val, height[now]);
        }
        now = rk_1 + 1;
        val = height[now];
        while (now <= N) {
            debug(val);
            ans += val;
            now++;
            val = min(val, height[now]);
        }
        return ans + N;
    }
};