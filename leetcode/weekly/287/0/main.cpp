#include "./solution.h"

int main() {
    Solution sol = Solution();
    int res[2] = {3, 1};
    string current[2] = {"02:30", "11:00"};
    string correct[2] = {"04:35", "11:01"};
    for (int i = 0; i < 2; i++) {
        int my_ans = sol.convertTime(current[i], correct[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}