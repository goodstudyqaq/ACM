#include "./solution.h"

int main() {
    Solution sol = Solution();
    int res[2] = {4, 0};
    TreeNode* root[2] = {new TreeNode({1,5,3,NULL,4,10,6,9,2}), new TreeNode({1})};
    int start[2] = {3, 1};
    for (int i = 0; i < 2; i++) {
        int my_ans = sol.amountOfTime(root[i], start[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}