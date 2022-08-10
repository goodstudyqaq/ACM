#include "./solution.h"

int main() {
    Solution sol = Solution();
    int res[2] = {4, 4};
    string s[2] = {"acfgbd", "abcd"};
    int k[2] = {2, 3};
    for (int i = 0; i < 2; i++) {
        int my_ans = sol.longestIdealString(s[i], k[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}