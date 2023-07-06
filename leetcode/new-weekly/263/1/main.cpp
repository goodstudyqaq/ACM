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
        vector<long long>&;
        convert_params(input_param[0], long > &);
        Bank sol = Bank(long > &);

        for (int j = 1; j < func_num; j++) {
            input_param = split_str_to_params(input_params[j]);
            if (function_names[j] == "transfer") {
                int account1;
                convert_params(input_param[0], account1);
                int account2;
                convert_params(input_param[1], account2);
                long long;
                convert_params(input_param[2], long);
                bool real_res;
                convert_params(output_params[j], real_res);
                bool my_res = sol.transfer(account1, account2, long);
                bool check_result = compare_result(to_string(i + 1) + "-" + to_string(j), my_res, real_res);
                all_test++;
                if (!check_result) fail_test++;
            }
            if (function_names[j] == "deposit") {
                int account;
                convert_params(input_param[0], account);
                long long;
                convert_params(input_param[1], long);
                bool real_res;
                convert_params(output_params[j], real_res);
                bool my_res = sol.deposit(account, long);
                bool check_result = compare_result(to_string(i + 1) + "-" + to_string(j), my_res, real_res);
                all_test++;
                if (!check_result) fail_test++;
            }
            if (function_names[j] == "withdraw") {
                int account;
                convert_params(input_param[0], account);
                long long;
                convert_params(input_param[1], long);
                bool real_res;
                convert_params(output_params[j], real_res);
                bool my_res = sol.withdraw(account, long);
                bool check_result = compare_result(to_string(i + 1) + "-" + to_string(j), my_res, real_res);
                all_test++;
                if (!check_result) fail_test++;
            }
        }
    }

    cerr << "总测试个数: " << all_test << endl;
    cerr << "错误个数: " << fail_test << endl;
    return 0;
}
