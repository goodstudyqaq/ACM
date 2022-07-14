#include "./solution.h"

int main() {
    Solution sol = Solution();
    bool res[3] = {true, false, false};
    string start[3] = {"_L__R__R_", "R_L_", "_R"};
    string target[3] = {"L______RR", "__LR", "R_"};
    for (int i = 0; i < 3; i++) {
        bool my_ans = sol.canChange(start[i], target[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}