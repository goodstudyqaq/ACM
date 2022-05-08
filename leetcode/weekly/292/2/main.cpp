#include "./solution.h"

int main() {
    Solution sol = Solution();
    int res[2] = {8, 82876089};
    string pressedKeys[2] = {"22233", "222222222222222222222222222222222222"};
    for (int i = 0; i < 2; i++) {
        int my_ans = sol.countTexts(pressedKeys[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}