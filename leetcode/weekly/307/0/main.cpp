#include "./solution.h"

int main() {
    Solution sol = Solution();
    int res[2] = {8, 0};
    int initialEnergy[2] = {5, 2};
    int initialExperience[2] = {3, 4};
    vector<int> energy[2] = {{1,4,3,2}, {1}};
    vector<int> experience[2] = {{2,6,3,1}, {3}};
    for (int i = 0; i < 2; i++) {
        int my_ans = sol.minNumberOfHours(initialEnergy[i], initialExperience[i], energy[i], experience[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}