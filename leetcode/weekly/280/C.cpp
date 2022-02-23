// copy_start_symbol=hello copy_end_symbol=world
#include "../../header.h"
//hello
class Solution {
   public:
    vector<long long> sum;

    long long minimumRemoval(vector<int>& beans) {
        sum.clear();
        int n = beans.size();
        sum.resize(n, 0);
        sort(beans.begin(), beans.end());
        for (int i = 0; i < n; i++) {
            sum[i] = beans[i];
            if (i != 0) {
                sum[i] += sum[i - 1];
            }
        }
        long long res = 1e11;
        for (int i = 0; i < n; i++) {
            long long tmp0 = 0;
            if (i != 0) {
                tmp0 = sum[i - 1];
            }
            int num = n - i - 1;
            long long tmp1 = (sum[n - 1] - sum[i]) - 1LL * num * beans[i];
            tmp0 += tmp1;
            res = min(tmp0, res);
        }
        return res;
    }
};

//world