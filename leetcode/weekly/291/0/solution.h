/*
Code generated by https://github.com/goodStudyTnT/leetcode-tester
*/

#if __has_include("../../utils/cpp/help.h")
#include "../../utils/cpp/help.h"
#endif

class Solution {
   public:
    string removeDigit(string number, char digit) {
        int n = number.size();
        string res = "";
        for (int i = n - 1; i >= 0; i--) {
            if (number[i] == digit) {
                string tmp = number;
                tmp.erase(tmp.begin() + i);
                res = max(res, tmp);
            }
        }
        return res;
    }
};