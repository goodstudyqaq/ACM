#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 5;
class Solution {
 public:
	int sum[maxn];
	bool canReach(string s, int minJump, int maxJump) {
		int n = s.size();
		vector< int > v;
		for (int i = 0; i < n; i++)
			if (s[i] == '0') {
				v.push_back(i);
			}
		sum[0] = 1;
		for (int i = 1; i < v.size(); i++) {
			int idx = v[i];
			int rval = idx - minJump;
			int lval = max(idx - maxJump, 0);
			if (rval < 0) {
				sum[i] = 0;
			} else {
				int l_idx = lower_bound(v.begin(), v.end(), lval) - v.begin();
				int r_idx = upper_bound(v.begin(), v.end(), rval) - v.begin();
				r_idx--;
				if (l_idx > r_idx) {
					sum[i] = 0;
				} else {
					int val = sum[r_idx];
					if (l_idx != 0) {
						val = val - sum[l_idx - 1];
					}
					if (val) {
						sum[i] = 1;
					}
				}
			}
			sum[i] += sum[i - 1];
		}
		if (v[v.size() - 1] != n - 1) {
			return false;
		}
		for (int i = 0; i < v.size(); i++) {
			cout << sum[i] << ' ';
		}
		return sum[v.size() - 1] - sum[v.size() - 2] > 0;
	}
};