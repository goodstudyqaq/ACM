#include "./solution.h"

int main() {
    Solution sol = Solution();
    string res[3] = {"2(47+38)", "1(2+3)4", "(999+999)"};
    string expression[3] = {"247+38", "12+34", "999+999"};
    for (int i = 0; i < 3; i++) {
        string my_ans = sol.minimizeResult(expression[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}