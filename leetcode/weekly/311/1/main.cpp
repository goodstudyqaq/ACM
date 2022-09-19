#include "./solution.h"

int main() {
    Solution sol = Solution();
    int res[2] = {2, 5};
    string s[2] = {"abacaba", "abcde"};
    for (int i = 0; i < 2; i++) {
        int my_ans = sol.longestContinuousSubstring(s[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}