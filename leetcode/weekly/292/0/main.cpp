#include "./solution.h"

int main() {
    Solution sol = Solution();
    string res[3] = {"777", "000", ""};
    string num[3] = {"6777133339", "2300019", "42352338"};
    for (int i = 0; i < 3; i++) {
        string my_ans = sol.largestGoodInteger(num[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}