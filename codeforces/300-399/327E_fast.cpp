#include <bits/stdc++.h>

using namespace std;

template < typename A, typename B >
string to_string(pair< A, B > p);

template < typename A, typename B, typename C >
string to_string(tuple< A, B, C > p);

template < typename A, typename B, typename C, typename D >
string to_string(tuple< A, B, C, D > p);

string to_string(const string& s) {
	return '"' + s + '"';
}

string to_string(const char* s) {
	return to_string(( string )s);
}

string to_string(bool b) {
	return (b ? "true" : "false");
}

string to_string(vector< bool > v) {
	bool first = true;
	string res = "{";
	for (int i = 0; i < static_cast< int >(v.size()); i++) {
		if (!first) {
			res += ", ";
		}
		first = false;
		res += to_string(v[i]);
	}
	res += "}";
	return res;
}

template < size_t N >
string to_string(bitset< N > v) {
	string res = "";
	for (size_t i = 0; i < N; i++) {
		res += static_cast< char >('0' + v[i]);
	}
	return res;
}

template < typename A >
string to_string(A v) {
	bool first = true;
	string res = "{";
	for (const auto& x : v) {
		if (!first) {
			res += ", ";
		}
		first = false;
		res += to_string(x);
	}
	res += "}";
	return res;
}

template < typename A, typename B >
string to_string(pair< A, B > p) {
	return "(" + to_string(p.first) + ", " + to_string(p.second) + ")";
}

template < typename A, typename B, typename C >
string to_string(tuple< A, B, C > p) {
	return "(" + to_string(get< 0 >(p)) + ", " + to_string(get< 1 >(p)) + ", " + to_string(get< 2 >(p)) + ")";
}

template < typename A, typename B, typename C, typename D >
string to_string(tuple< A, B, C, D > p) {
	return "(" + to_string(get< 0 >(p)) + ", " + to_string(get< 1 >(p)) + ", " + to_string(get< 2 >(p)) + ", " + to_string(get< 3 >(p)) + ")";
}

void debug_out() {
	cerr << endl;
}

template < typename Head, typename... Tail >
void debug_out(Head H, Tail... T) {
	cerr << " " << to_string(H);
	debug_out(T...);
}

#ifdef LOCAL
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
#else
#define debug(...) 42
#endif

vector< int > a;
int n;
// 阶乘
vector< int > A;
const int mod = 1e9 + 7;
void init() {
	A[0] = 1;
	for (int i = 1; i <= n; i++) {
		A[i] = 1LL * A[i - 1] * i % mod;
	}
}

typedef pair< long long, int > pli;
void group1(int now_idx, int end_idx, long long val, int num, vector< pli >& res, int& res_cnt) {
	if (now_idx > end_idx) {
		res[res_cnt++] = { val, num };
		return;
	}
	group1(now_idx + 1, end_idx, val + a[now_idx], num + 1, res, res_cnt);
	group1(now_idx + 1, end_idx, val, num, res, res_cnt);
}

void my_unique(vector< pli >& res, int sz, map< pli, int >& cnt) {
	int now_idx = 0;
	int now = 0;
	while (now < sz) {
		int go = now;
		while (go < sz && res[now] == res[go]) go++;
		res[now_idx++] = res[now];
		cnt[res[now]] = go - now;
		now = go;
	}
	res.resize(now_idx);
}

int work1(long long limit) {
	// meet in the middle
	//[0, n / 2], [n / 2 + 1, n - 1]
	int idx = n / 2;
	vector< pli > res1, res2;

	// res1 有 idx + 1 个数
	res1.resize(1 << (idx + 1));
	if (n - idx - 1 > 0) {
		res2.resize(1 << (n - idx - 1));
	} else {
		res2.resize(1);
	}
	int res1_cnt = 0, res2_cnt = 0;
	group1(0, idx, 0, 0, res1, res1_cnt);
	group1(idx + 1, n - 1, 0, 0, res2, res2_cnt);
	sort(res1.begin(), res1.begin() + res1_cnt);
	sort(res2.begin(), res2.begin() + res2_cnt);

	// for (int i = 0; i < res1.size(); i++) {
	// 	debug(res1[i].first, res1[i].second);
	// }

	map< pli, int > cnt1, cnt2;
	my_unique(res1, res1_cnt, cnt1);
	my_unique(res2, res2_cnt, cnt2);

	int now_res1_idx = 0, now_res2_idx = res2.size() - 1;
	int ans = 0;
	while (now_res1_idx < res1.size() && now_res2_idx >= 0) {
		long long val = res1[now_res1_idx].first + res2[now_res2_idx].first;
		if (val < limit) {
			now_res1_idx++;
		} else if (val > limit) {
			now_res2_idx--;
		} else {
			for (int i = now_res2_idx; i >= 0; i--) {
				if (res1[now_res1_idx].first + res2[i].first == limit) {
					int num1 = res1[now_res1_idx].second, num2 = res2[i].second;
					ans = (ans + 1LL * A[num1 + num2] * A[n - num1 - num2] % mod * cnt1[res1[now_res1_idx]] % mod * cnt2[res2[i]] % mod) % mod;
				} else {
					break;
				}
			}
			now_res1_idx++;

			// debug(ans, res1[now_res1_idx].first, res1[now_res1_idx].second, res2[now_res2_idx].first, res2[now_res2_idx].second);
		}
	}
	return ans;
}

typedef pair< long long, long long > pll;
typedef pair< int, int > pii;
typedef pair< pll, pii > pllii;

void group2(int now_idx, int end_idx, long long val1, int num1, long long val2, int num2, vector< pllii >& res, int& res_cnt) {
	if (now_idx > end_idx) {
		res[res_cnt++] = { { val1, val2 }, { num1, num2 } };
		return;
	}
	group2(now_idx + 1, end_idx, val1, num1, val2, num2, res, res_cnt);
	group2(now_idx + 1, end_idx, val1 + a[now_idx], num1 + 1, val2, num2, res, res_cnt);
	group2(now_idx + 1, end_idx, val1, num1, val2 + a[now_idx], num2 + 1, res, res_cnt);
}

void my_unique2(vector< pllii >& res, int sz, map< pllii, int >& cnt) {
	int now_idx = 0;
	int now = 0;
	while (now < sz) {
		int go = now;
		while (go < sz && res[now] == res[go]) go++;
		res[now_idx++] = res[now];
		cnt[res[now]] = go - now;
		now = go;
	}
	res.resize(now_idx);
}

int quick(int a, int b) {
	int res = 1;
	while (b) {
		if (b % 2) res = res * a;
		b /= 2;
		a = a * a;
	}
	return res;
}

int work2(long long limit1, long long limit2) {
	int ans1 = work1(limit1);
	int ans2 = work1(limit2);
	debug(limit1, limit2, ans1, ans2);
	vector< pllii > res1, res2;
	int idx = n / 2;

	res1.resize(quick(3, idx + 1));
	if (n - idx - 1 > 0) {
		res2.resize(quick(3, n - idx - 1));
	} else {
		res2.resize(1);
	}
	int res1_cnt = 0, res2_cnt = 0;

	group2(0, idx, 0, 0, 0, 0, res1, res1_cnt);
	group2(idx + 1, n - 1, 0, 0, 0, 0, res2, res2_cnt);

	sort(res1.begin(), res1.begin() + res1_cnt);
	sort(res2.begin(), res2.begin() + res2_cnt);

	// for (int i = 0; i < res1.size(); i++) {
	// 	debug(res1[i].first.first, res1[i].first.second, res1[i].second.first, res1[i].second.second);
	// }
	// for (int i = 0; i < res2.size(); i++) {
	// 	debug(res2[i].first.first, res2[i].first.second, res2[i].second.first, res2[i].second.second);
	// }

	map< pllii, int > cnt1, cnt2;
	my_unique2(res1, res1_cnt, cnt1);
	my_unique2(res2, res2_cnt, cnt2);

	int now_res1_idx = 0, now_res2_idx = res2.size() - 1;
	int ans = 0;
	while (now_res1_idx < res1.size() && now_res2_idx >= 0) {

		long long val = res1[now_res1_idx].first.first + res2[now_res2_idx].first.first;
		if (val < limit1) {
			now_res1_idx++;
		} else if (val > limit1) {
			now_res2_idx--;
		} else {
			long long val2 = res1[now_res1_idx].first.second + res2[now_res2_idx].first.second;
			if (val2 < limit2) {
				now_res1_idx++;
			} else if (val2 > limit2) {
				now_res2_idx--;
			} else {
				for (int i = now_res2_idx; i >= 0; i--) {
					if (res1[now_res1_idx].first.first + res2[i].first.first == limit1 && res1[now_res1_idx].first.second + res2[i].first.second == limit2) {
						int num1 = res1[now_res1_idx].second.first + res2[i].second.first;
						int num2 = res1[now_res1_idx].second.second + res2[i].second.second;
						ans = (ans + 1LL * A[num1] * A[num2] % mod * A[n - num1 - num2] % mod * cnt1[res1[now_res1_idx]] % mod * cnt2[res2[i]] % mod) % mod;
					} else {
						break;
					}
				}
				now_res1_idx++;
			}
		}
	}
	debug(ans1, ans2, ans);
	int real_ans = (((A[n] - ans1) % mod - ans2) % mod + ans) % mod;
	real_ans = (real_ans + mod) % mod;

	return real_ans;
}

int main() {
#ifdef LOCAL
	freopen("data.in", "r", stdin);
#endif
	ios::sync_with_stdio(false);
	cin.tie(0);

	cin >> n;
	a.resize(n + 1);
	A.resize(n + 1);
	long long sum = 0;
	for (int i = 0; i < n; i++) {
		cin >> a[i];
		sum += a[i];
	}
	int k;
	cin >> k;
	vector< int > limit;
	limit.resize(k);
	for (int i = 0; i < k; i++) {
		cin >> limit[i];
	}
	init();
	if (k == 0) {
		cout << A[n] << endl;
	} else if (k == 1) {
		int ans = work1(limit[0]);
		ans = (A[n] - ans) % mod;
		ans = (ans + mod) % mod;
		cout << ans << endl;
	} else {
		if (limit[0] > limit[1]) {
			swap(limit[0], limit[1]);
		}
		int ans = work2(limit[0], sum - limit[1]);

		cout << ans << endl;
	}
	return 0;
}