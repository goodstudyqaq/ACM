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
int k;

const int mod = 998244353;
vector< int > v;
vector< vector< int > > dp, dp2;
vector< int > ten;
typedef pair< int, int > pii;

pii dfs(int d, int status, int num, bool limit, bool lead) {
	// 前面是个数， 后面是和
	if (num > k) {
		return { 0, 0 };
	}
	if (d == -1) {
		return { 1, 0 };
	}

	if (!limit && !lead && dp[d][status] != -1) return { dp[d][status], dp2[d][status] };
	int res_num = 0;
	int res_sum = 0;
	int LIMIT = limit ? v[d] : 9;

	for (int i = 0; i <= LIMIT; i++) {
		int new_num = num;
		if (((status >> i) & 1) == 0) new_num++;
		if (i == 0) {
			if (lead) {
				pii tmp = dfs(d - 1, status, num, limit && i == LIMIT, lead);
				res_num = (res_num + tmp.first) % mod;
				res_sum = (res_sum + tmp.second) % mod;
			} else {
				pii tmp = dfs(d - 1, status | (1 << i), new_num, limit && i == LIMIT, lead && i == 0);
				res_num = (res_num + tmp.first) % mod;
				res_sum = (res_sum + tmp.second) % mod;
			}
		} else {
			pii tmp = dfs(d - 1, status | (1 << i), new_num, limit && i == LIMIT, lead && i == 0);
			res_num = (res_num + tmp.first) % mod;
			res_sum = (res_sum + (1LL * i * ten[d] % mod * tmp.first % mod + tmp.second) % mod) % mod;
		}
	}
	if (!lead && !limit) {
		dp[d][status] = res_num;
		dp2[d][status] = res_sum;
	}
	return { res_num, res_sum };
}

int work(long long num) {
	v.clear();
	while (num) {
		v.push_back(num % 10);
		num /= 10;
	}
	return dfs(v.size() - 1, 0, 0, true, true).second;
}

int main() {
#ifdef LOCAL
	freopen("data.in", "r", stdin);
#endif
	ios::sync_with_stdio(false);
	cin.tie(0);

	long long l, r;
	cin >> l >> r >> k;
	dp.resize(20, vector< int >(1 << 10, -1));
	dp2.resize(20, vector< int >(1 << 10, -1));
	ten.resize(20);
	ten[0] = 1;
	for (int i = 1; i < 20; i++) {
		ten[i] = 1LL * ten[i - 1] * 10 % mod;
	}
	// for (int i = 1; i <= 50; i++) {
	// 	debug(i, work(i));
	// }
	cout << ((work(r) - work(l - 1)) % mod + mod) % mod << endl;
	return 0;
}