#include "./solution.h"

int main() {
    Solution sol = Solution();
    string res[2] = {"lecoe", ""};
    string s[2] = {"leet**cod*e", "erase*****"};
    for (int i = 0; i < 2; i++) {
        string my_ans = sol.removeStars(s[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}