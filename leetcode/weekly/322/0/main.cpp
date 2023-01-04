#include "./solution.h"

int main() {
    Solution sol = Solution();
    bool res[3] = {true, true, false};
    string sentence[3] = {"leetcode exercises sound delightful", "eetcode", "Leetcode is cool"};
    for (int i = 0; i < 3; i++) {
        bool my_ans = sol.isCircularSentence(sentence[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}