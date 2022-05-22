#include "./solution.h"

int main() {
    Solution sol = Solution();
    int res[2] = {33, 0};
    string s[2] = {"foobar", "jjjj"};
    char letter[2] = {"o", "k"};
    for (int i = 0; i < 2; i++) {
        int my_ans = sol.percentageLetter(s[i], letter[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}