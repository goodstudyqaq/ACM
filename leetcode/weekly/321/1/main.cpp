#include "./solution.h"

int main() {
    Solution sol = Solution();
    int res[3] = {4, 0, 5};
    string s[3] = {"coaching", "abcde", "z"};
    string t[3] = {"coding", "a", "abcde"};
    for (int i = 0; i < 3; i++) {
        int my_ans = sol.appendCharacters(s[i], t[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}