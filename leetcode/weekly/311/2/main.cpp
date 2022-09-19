#include "./solution.h"

int main() {
    Solution sol = Solution();
    TreeNode* res[3] = {new TreeNode({2,5,3,8,13,21,34}), new TreeNode({7,11,13}), new TreeNode({0,2,1,0,0,0,0,2,2,2,2,1,1,1,1})};
    TreeNode* root[3] = {new TreeNode({2,3,5,8,13,21,34}), new TreeNode({7,13,11}), new TreeNode({0,1,2,0,0,0,0,1,1,1,1,2,2,2,2})};
    for (int i = 0; i < 3; i++) {
        TreeNode* my_ans = sol.reverseOddLevels(root[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}