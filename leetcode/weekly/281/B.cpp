// copy_start_symbol=hello copy_end_symbol=world
#include "../../header.h"

struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

// hello
class Solution {
   public:
    ListNode* mergeNodes(ListNode* head) {
        ListNode* now = head;
        ListNode* ans = nullptr;
        ListNode* last = nullptr;
        while (now != nullptr) {
            ListNode* go = now->next;
            ListNode* beg = now->next;
            if (go == nullptr) break;
            int val = 0;
            while (go->val != 0) {
                val += go->val;
                go = go->next;
            }
            cout << val << endl;
            beg->val = val;
            beg->next = nullptr;
            if (ans == nullptr) {
                ans = beg;
                last = beg;
            } else {
                last->next = beg;
                last = last->next;
            }
            now = go;
        }
        return ans;
    }
};
// world