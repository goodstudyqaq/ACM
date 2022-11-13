#include "./solution.h"

int main() {
    Solution sol = Solution();
    int res[3] = {3, 3, 0};
    TreeNode* root[3] = {new TreeNode({1,4,3,7,6,8,5,NULL,NULL,NULL,NULL,9,NULL,10}), new TreeNode({1,3,2,7,6,5,4}), new TreeNode({1,2,3,4,5,6})};
    for (int i = 0; i < 3; i++) {
        int my_ans = sol.minimumOperations(root[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}