#include "./solution.h"

int main() {
    ifstream infile;
    infile.open("./data", ios::in);
    string strLine;
    int one_test_number = 3;  // 固定 3 行，函数，入参，出参
    vector<string> data;
    while (getline(infile, strLine)) {
        if (strLine.size()) {
            data.push_back(strLine);
        }
    }
    if (data.size() % (one_test_number)) {
        cerr << "测试数据格式不正确" << endl;
        return 0;
    }
    int all_test = 0, fail_test = 0;
    int test_number = data.size() / one_test_number;
    for (int i = 0; i < test_number; i++) {
        cerr << "样例" << to_string(i + 1) + " 测试中..." << endl;
        vector<string> function_names = split_str_to_func(data[i * one_test_number + 0]);
        vector<string> input_params = split_str_to_params(data[i * one_test_number + 1]);
        vector<string> output_params = split_str_to_params(data[i * one_test_number + 2]);
        vector<string> input_param;

        // 第 0 个一般是初始化
        input_param = split_str_to_params(input_params[0]);
        int func_num = function_names.size();
        SmallestInfiniteSet sol = SmallestInfiniteSet();

        for (int j = 1; j < func_num; j++) {
            input_param = split_str_to_params(input_params[j]);
            if (function_names[j] == "popSmallest") {
                int real_res;
                convert_params(output_params[j], real_res);
                int my_res = sol.popSmallest();
                bool check_result = compare_result(to_string(i + 1) + "-" + to_string(j), my_res, real_res);
                all_test++;
                if (!check_result) fail_test++;
            }
            if (function_names[j] == "addBack") {
                int num;
                convert_params(input_param[0], num);
                sol.addBack(num);
            }
        }
    }

    cerr << "总测试个数: " << all_test << endl;
    cerr << "错误个数: " << fail_test << endl;
    return 0;
}
