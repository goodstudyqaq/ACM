#include <bits/stdc++.h>

#include "./copypaste/dataStruct/rmq.h"
using namespace std;
//SA[i]=a 排名为i的下标为a
//rank[a]=i 下标为a的排名为i
//height[i]=a 排名为i的和排名为i-1是最长公共前缀
//下标从1到N 千万不能搞错
struct SuffixArray {
    vector<int> SA, rank, height;
    int N;
    RMQ<int> rmq;
    SuffixArray(string& s) {
        vector<int> cntA, cntB, A, B, tsa, ch;
        N = s.size();
        int mx_element = *max_element(s.begin(), s.end());
        int M = max(N, mx_element);
        ch.resize(N + 1);
        cntA.resize(M + 1, 0);
        cntB.resize(N + 1, 0);
        SA.resize(N + 1);
        rank.resize(N + 1);
        A.resize(N + 1);
        B.resize(N + 1);
        tsa.resize(N + 1);
        height.resize(N + 1);

        for (int i = 1; i <= N; i++) {
            ch[i] = s[i - 1];
        }
        for (int i = 1; i <= N; i++) {
            cntA[ch[i]]++;
        }

        for (int i = 1; i <= mx_element; i++) {
            cntA[i] += cntA[i - 1];
        }

        for (int i = N; i >= 1; i--) {
            SA[cntA[ch[i]]--] = i;
        }
        rank[SA[1]] = 1;
        for (int i = 2; i <= N; i++) {
            rank[SA[i]] = rank[SA[i - 1]];
            if (ch[SA[i]] != ch[SA[i - 1]])
                rank[SA[i]]++;
        }
        // debug(SA);
        for (int step = 1; rank[SA[N]] < N; step <<= 1) {
            // debug(step, SA[N], rank[SA[N]]);
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
        int i, j, k = 0;
        for (int i = 1; i <= N; i++) {
            if (k) k--;
            j = SA[rank[i] - 1];
            while (i + k <= N && j + k <= N && ch[i + k] == ch[j + k]) k++;
            height[rank[i]] = k;
        }
        rmq.build(height, [&](int a, int b) -> bool {
            return a < b;
        });
    }

    int get_length(int idx1, int idx2) {
        // s 的下标
        int rk_idx1 = rank[idx1 + 1], rk_idx2 = rank[idx2 + 1];
        if (rk_idx1 > rk_idx2) {
            swap(rk_idx1, rk_idx2);
        }
        return rmq.rmq_value(rk_idx1 + 1, rk_idx2 + 1);
    }
};
