#include "./solution.h"

int main() {
    Solution sol = Solution();
    vector<long long> res[2] = {{101,111,121,131,141,999}, {1111,1331,1551}};
    vector<int> queries[2] = {{1,2,3,4,5,90}, {2,4,6}};
    int intLength[2] = {3, 4};
    for (int i = 0; i < 2; i++) {
        vector<long long> my_ans = sol.kthPalindrome(queries[i], intLength[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}