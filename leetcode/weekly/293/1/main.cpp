#include "./solution.h"

int main() {
    Solution sol = Solution();
    int res[2] = {3, 0};
    int bottom[2] = {2, 6};
    int top[2] = {9, 8};
    vector<int> special[2] = {{4,6}, {7,6,8}};
    for (int i = 0; i < 2; i++) {
        int my_ans = sol.maxConsecutive(bottom[i], top[i], special[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}