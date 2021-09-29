#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#define MAX_LINE 110000

using namespace std;
int isNaN(float f) {
    unsigned long x = *(unsigned long*)&f;
    return 0 != (x & 0x7ffffful) && 0x7f800000ul == (x & 0x7f800000ul);
}

int main(int argc, char* argv[]) {
    char output_line[MAX_LINE] = {0};
    char pout_line[MAX_LINE] = {0};
    //ifstream output(argv[2]);
    ifstream output("output");
    ifstream pout("user_output");
    int line_no = 1;
    int error_line_no = 0;
    while (output.getline(output_line, MAX_LINE)) {
        pout.getline(pout_line, MAX_LINE);
        double foutput = atof(output_line);
        double fpout = atof(pout_line);
        if (isNaN(fpout) && error_line_no == 0) {
            error_line_no = line_no;
        }
        // 浮点数的output规范是5位小数
        if (fabs(foutput - fpout) / max(1.0, fabs(foutput)) > 1e-5 && error_line_no == 0) {
            error_line_no = line_no;
        }
        ++line_no;
    }

    while (error_line_no == 0 && pout.getline(pout_line, MAX_LINE)) {
        error_line_no = line_no - 1;
        break;
    }

    if (error_line_no > 0) {
        return 1;
    }
    return 0;
}
