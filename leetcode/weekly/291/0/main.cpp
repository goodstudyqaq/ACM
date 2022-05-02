#include "./solution.h"

int main() {
    Solution sol = Solution();
    string res[3] = {"12", "231", "51"};
    string number[3] = {"123", "1231", "551"};
    char digit[3] = {'3', '1', '5'};
    for (int i = 0; i < 3; i++) {
        string my_ans = sol.removeDigit(number[i], digit[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}