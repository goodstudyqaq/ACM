// copy_start_symbol=hello copy_end_symbol=world
#include "../header.h"

// hello
#define lowbit(x) x & -x
const int maxn = 1e5 + 5;
int sum[maxn];
void add(int x, int val) {
    while (x < maxn) {
        sum[x] += val;
        x += lowbit(x);
    }
}

int query(int x) {
    int res = 0;
    while (x) {
        res += sum[x];
        x -= lowbit(x);
    }
    return res;
}

class Solution {
   public:
    vector<int> idx2;
    vector<int> sum1;
    long long goodTriplets(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size();
        sum1.clear(), sum1.resize(n);
        idx2.resize(n);

        memset(sum, 0, sizeof(sum));
        for (int i = 0; i < nums2.size(); i++) {
            idx2[nums2[i]] = i + 1;
        }

        for (int i = 0; i < n; i++) {
            int val = nums1[i];
            int the_idx2 = idx2[val];
            sum1[val] = query(the_idx2 - 1);
            add(the_idx2, 1);
        }
        memset(sum, 0, sizeof(sum));

        long long res = 0;
        for (int i = n - 1; i >= 0; i--) {
            int val = nums1[i];
            int the_idx2 = n + 1 - idx2[val];
            int tmp = query(the_idx2 - 1);
            // cout << val << ' ' << sum1[val] << ' ' << tmp << endl;
            res += 1LL * sum1[val] * tmp;
            add(the_idx2, 1);
        }
        return res;
    }
};

// world
int main() {
    // [13,14,10,2,12,3,9,11,15,8,4,7,0,6,5,1]
    // [8,7,9,5,6,14,15,10,2,11,4,13,3,12,1,0]
    vector<int> a({13, 14, 10, 2, 12, 3, 9, 11, 15, 8, 4, 7, 0, 6, 5, 1});
    vector<int> b({8, 7, 9, 5, 6, 14, 15, 10, 2, 11, 4, 13, 3, 12, 1, 0});
    Solution sol = Solution();
    cout << sol.goodTriplets(a, b) << endl;
    int n = a.size();
    vector<int> idx(n);
    for (int i = 0; i < n; i++) {
        idx[b[i]] = i;
    }
    auto check = [&](int a, int b, int c) {
        return idx[a] < idx[b] && idx[b] < idx[c];
    };

    vector<int> ans(n, 0);
    int res = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            for (int k = j + 1; k < n; k++) {
                if (check(a[i], a[j], a[k])) {
                    ans[j]++;
                    res++;
                }
            }
        }
    }
    cout << res << endl;
    return 0;
}