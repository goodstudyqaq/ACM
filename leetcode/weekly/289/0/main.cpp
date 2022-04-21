#include "./solution.h"

int main() {
    Solution sol = Solution();
    string res[2] = {"135", "000"};
    string s[2] = {"11111222223", "00000000"};
    int k[2] = {3, 3};
    for (int i = 0; i < 2; i++) {
        string my_ans = sol.digitSum(s[i], k[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}