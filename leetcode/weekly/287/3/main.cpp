#include "./solution.h"

void test0(){
    vector<char> keys[1] = {{"a", "b", "c", "d"}};
    vector<string> values[1] = {{"ei", "zf", "ei", "am"}};
    vector<string> dictionary[1] = {{"abcd", "acbd", "adbc", "badc", "dacb", "cadb", "cbda", "abad"}};
    string word1[1] = {"abcd"};
    string word2[1] = {"eizfeiam"};
    Encrypter *obj = new Encrypter(keys[0], values[0], dictionary[0]);
    string res0 = obj->encrypt(word1[0]);
    string ans0 = "eizfeiam";
    compare_result("0-0", res0, ans0);
    int res1 = obj->decrypt(word2[0]);
    int ans1 = 2;
    compare_result("0-1", res1, ans1);
}

int main() {
    test0();
    return 0;
}
