class Solution {
   public:
    int transportationHub(vector<vector<int>>& p) {
        const int maxn = 1000;

        int m = p.size();
        vector<int> in(maxn + 1);
        vector<int> out(maxn + 1);

        set<int> S;

        for (int i = 0; i < m; i++) {
            int u = p[i][0], v = p[i][1];
            in[v]++;
            out[u]++;
            S.insert(u);
            S.insert(v);
        }
        int sz = S.size();
        for (int i = 0; i <= maxn; i++) {
            if (in[i] == sz - 1 && out[i] == 0) {
                return i;
            }
        }
        return -1;
    }
};
