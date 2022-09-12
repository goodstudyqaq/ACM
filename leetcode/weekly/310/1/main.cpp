#include "./solution.h"

int main() {
    Solution sol = Solution();
    int res[2] = {4, 6};
    string s[2] = {"abacaba", "ssssss"};
    for (int i = 0; i < 2; i++) {
        int my_ans = sol.partitionString(s[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}