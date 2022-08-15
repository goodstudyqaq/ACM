#include "./solution.h"

int main() {
    Solution sol = Solution();
    int res[3] = {19, 5, 110};
    int n[3] = {20, 5, 135};
    for (int i = 0; i < 3; i++) {
        int my_ans = sol.countSpecialNumbers(n[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}