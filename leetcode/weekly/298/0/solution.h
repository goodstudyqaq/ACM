/*
Code generated by https://github.com/goodStudyTnT/leetcode-tester
*/

#if __has_include("../../utils/cpp/help.h")
#include "../../utils/cpp/help.h"
#endif

#ifdef LOCAL
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
#else
#define debug(...) 42
#endif

class Solution {
   public:
    string greatestLetter(string s) {
        int n = s.size();
        set<char> S;
        for (int i = 0; i < n; i++) {
            S.insert(s[i]);
        }

        char res = ' ';
        for (char it = 'a'; it <= 'z'; it++) {
            char it2 = it - 'a' + 'A';
            if (S.count(it) && S.count(it2)) {
                res = it2;
            }
        }
        if (res == ' ') {
            return "";
        } else {
            string res2 = "";
            res2 += res;
            return res2;
        }
    }
};