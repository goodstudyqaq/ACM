#include "./solution.h"

int main() {
    Solution sol = Solution();
    int res[3] = {5, -1, 94};
    vector<int> nums[3] = {{5, 2, 2, 4, 0, 6}, {2}, {35, 43, 23, 86, 23, 45, 84, 2, 18, 83, 79, 28, 54, 81, 12, 94, 14, 0, 0, 29, 94, 12, 13, 1, 48, 85, 22, 95, 24, 5, 73, 10, 96, 97, 72, 41, 52, 1, 91, 3, 20, 22, 41, 98, 70, 20, 52, 48, 91, 84, 16, 30, 27, 35, 69, 33, 67, 18, 4, 53, 86, 78, 26, 83, 13, 96, 29, 15, 34, 80, 16, 49}};
    int k[3] = {4, 1, 15};
    for (int i = 0; i < 3; i++) {
        int my_ans = sol.maximumTop(nums[i], k[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}