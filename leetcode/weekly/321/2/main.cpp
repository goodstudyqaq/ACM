#include "./solution.h"

int main() {
    Solution sol = Solution();
    ListNode* res[2] = {new ListNode({13,8}), new ListNode({1,1,1,1})};
    ListNode* head[2] = {new ListNode({5,2,13,3,8}), new ListNode({1,1,1,1})};
    for (int i = 0; i < 2; i++) {
        ListNode* my_ans = sol.removeNodes(head[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}