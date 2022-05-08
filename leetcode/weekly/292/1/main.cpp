#include "./solution.h"

int main() {
    Solution sol = Solution();
    int res[2] = {5, 1};
    TreeNode* root[2] = {new TreeNode({4,8,5,0,1,NULL,6}), new TreeNode({1})};
    for (int i = 0; i < 2; i++) {
        int my_ans = sol.averageOfSubtree(root[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}