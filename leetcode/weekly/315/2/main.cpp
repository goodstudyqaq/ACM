#include "./solution.h"

int main() {
    Solution sol = Solution();
    bool res[3] = {true, false, true};
    int num[3] = {443, 63, 181};
    for (int i = 0; i < 3; i++) {
        bool my_ans = sol.sumOfNumberAndReverse(num[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}