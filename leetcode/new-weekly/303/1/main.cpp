#include "./solution.h"

int main() {
    Solution sol = Solution();
    // 读文件
    ifstream infile;
    infile.open("./data", ios::in);
    string strLine;

    int input_number = 1;
    int output_number = 1;
    int one_test_number = input_number + output_number;
    vector<string> data;

    while (getline(infile, strLine)) {
        if (strLine.size()) {
            // 避免回车
            data.push_back(strLine);
        }
    }
    if (data.size() % (one_test_number)) {
        cerr << "测试数据格式不正确！" << endl;
        return 0;
    }
    int test_number = data.size() / one_test_number;

    int all_test = test_number;
    int fail_test = 0;

    for (int i = 0; i < test_number; i++) {
        cerr << "样例" << to_string(i + 1) + " 测试中..." << endl;

        vector<vector<int>> grid;
        convert_params(data[i * one_test_number + 0], grid);
        int real_res;
        convert_params(data[i * one_test_number + 1], real_res);

        int my_res = sol.equalPairs(grid);

        bool check_result = compare_result(to_string(i + 1), my_res, real_res);
        if (!check_result) {
            fail_test++;
        }
    }
    cerr << "总测试个数: " << all_test << endl;
    cerr << "错误个数: " << fail_test << endl;
    return 0;
}