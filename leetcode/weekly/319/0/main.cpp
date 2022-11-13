#include "./solution.h"

int main() {
    Solution sol = Solution();
    vector<double> res[2] = {{309.65000,97.70000}, {395.26000,251.79800}};
    double celsius[2] = {36.50, 122.11};
    for (int i = 0; i < 2; i++) {
        vector<double> my_ans = sol.convertTemperature(celsius[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}