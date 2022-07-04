#include "./solution.h"

int main() {
    Solution sol = Solution();
    int res[2] = {5, 6};
    string s[2] = {"1001010", "00101001"};
    int k[2] = {5, 1};
    for (int i = 0; i < 2; i++) {
        int my_ans = sol.longestSubsequence(s[i], k[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}