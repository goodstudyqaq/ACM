#include "./solution.h"

void test0(){
    string text[2] = {"leetcode", "practice"};
    int k[2] = {4, 10};
    int k1[2] = {8, 2};
    int k0[2] = {3, 6};
    TextEditor *obj = new TextEditor();
    obj->addText(text[0]);
    int res0 = obj->deleteText(k[0]);
    int ans0 = 4;
    compare_result("0-0", res0, ans0);
    obj->addText(text[1]);
    string res1 = obj->cursorRight(k0[0]);
    string ans1 = "etpractice";
    compare_result("0-1", res1, ans1);
    string res2 = obj->cursorLeft(k1[0]);
    string ans2 = "leet";
    compare_result("0-2", res2, ans2);
    int res3 = obj->deleteText(k[1]);
    int ans3 = 4;
    compare_result("0-3", res3, ans3);
    string res4 = obj->cursorLeft(k1[1]);
    string ans4 = "";
    compare_result("0-4", res4, ans4);
    string res5 = obj->cursorRight(k0[1]);
    string ans5 = "practi";
    compare_result("0-5", res5, ans5);
}

int main() {
    test0();
    return 0;
}
