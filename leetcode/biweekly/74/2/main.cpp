#include "./solution.h"

int main() {
    Solution sol = Solution();
    int res[2] = {29, 2};
    vector<int> nums[2] = {{18,22,62,61,1,88,17,98,38,32,51,57,7,29,40,61,62,13,89,41,73,85,88,60,59,76,71,76,76,41,29,43,19,9,79}, {1,1}};
    for (int i = 0; i < 2; i++) {
        int my_ans = sol.halveArray(nums[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}