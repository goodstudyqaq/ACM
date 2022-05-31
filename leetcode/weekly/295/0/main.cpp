#include "./solution.h"

int main() {
    Solution sol = Solution();
    int res[3] = {2, 1, 1};
    string s[3] = {"ilovecodingonleetcode", "abcba", "abbaccaddaeea"};
    string target[3] = {"code", "abc", "aaaaa"};
    for (int i = 0; i < 3; i++) {
        int my_ans = sol.rearrangeCharacters(s[i], target[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}