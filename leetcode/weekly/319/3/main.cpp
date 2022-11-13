#include "./solution.h"

int main() {
    Solution sol = Solution();
    int res[2] = {2, 0};
    string s[2] = {"abaccdbbd", "adbcda"};
    int k[2] = {3, 2};
    for (int i = 0; i < 2; i++) {
        int my_ans = sol.maxPalindromes(s[i], k[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}