class Solution {
   public:
    int temperatureTrend(vector<int>& a, vector<int>& b) {
        auto work = [&](vector<int>& x) {
            int n = x.size();
            vector<int> V;
            for (int i = 0; i < n - 1; i++) {
                int tmp = x[i + 1] - x[i];
                if (tmp > 0) {
                    V.push_back(1);
                } else if (tmp == 0) {
                    V.push_back(0);
                } else {
                    V.push_back(-1);
                }
            }
            return V;
        };

        auto a1 = work(a);
        auto b1 = work(b);

        int sz = a1.size();

        int now = 0;
        int res = 0;
        while (now < sz) {
            int go1 = now;
            while (go1 < sz && a1[go1] != b1[go1]) go1++;
            if (go1 == sz) break;
            int go2 = go1;
            while (go2 < sz && a1[go2] == b1[go2]) go2++;
            res = max(res, go2 - go1);
            now = go2;
        }
        return res;
    }
};