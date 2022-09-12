#include "./solution.h"

int main() {
    Solution sol = Solution();
    int res[3] = {2, 4, -1};
    vector<int> nums[3] = {{0,1,2,2,4,4,1}, {4,4,4,9,2,4}, {29,47,21,41,13,37,25,7}};
    for (int i = 0; i < 3; i++) {
        int my_ans = sol.mostFrequentEven(nums[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}