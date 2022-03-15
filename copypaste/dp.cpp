#include <bits/stdc++.h>
using namespace std;
namespace SOSDP {
// https://codeforces.com/blog/entry/45223
/*
    F[mask] = \sum_{i \in mask} A[i]
    Time: O(N2^N)
*/

void iterative_version(int N, vector<int>& A) {
    //iterative version
    vector<vector<int>> dp(1 << N, vector<int>(N + 1));
    vector<int> F(1 << N);
    for (int mask = 0; mask < (1 << N); ++mask) {
        dp[mask][0] = A[mask];  //handle base case separately (leaf states)
        for (int i = 0; i < N; ++i) {
            if (mask & (1 << i)) {
                dp[mask][i + 1] = dp[mask][i] + dp[mask ^ (1 << i)][i];
            } else {
                dp[mask][i + 1] = dp[mask][i];
            }
        }
        F[mask] = dp[mask][N];
    }
}

void easy_version(int N, vector<int>& A) {
    vector<int> F(1 << N);
    //memory optimized, super easy to code.
    for (int i = 0; i < (1 << N); ++i) {
        F[i] = A[i];
    }
    for (int i = 0; i < N; ++i) {
        for (int mask = 0; mask < (1 << N); ++mask) {
            if (mask & (1 << i)) {
                F[mask] += F[mask ^ (1 << i)];
            }
        }
    }
}

}  // namespace SOSDP