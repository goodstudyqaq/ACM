#include "./solution.h"

int main() {
    Solution sol = Solution();
    char res[2] = {"c", "d"};
    string s[2] = {"abccbaacz", "abcdd"};
    for (int i = 0; i < 2; i++) {
        char my_ans = sol.repeatedCharacter(s[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}