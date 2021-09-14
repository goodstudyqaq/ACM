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
const int inf = 1e9 + 1;

struct Node {
	string s;
	char pre, suf;
	int pre_num, suf_num;
	int mx_len[26];
	bool only_one;

	void out() {
		cout << pre << ' ' << suf << endl;
		debug(pre_num, suf_num, only_one);
		for (int i = 0; i < 26; i++) {
			cout << mx_len[i] << ' ';
		}
		cout << endl;
	}

	void work() {
		int sz = s.size();
		pre = s[0];
		suf = s[sz - 1];

		vector< int > mx(sz);
		memset(mx_len, 0, sizeof(mx_len));
		for (int i = 0; i < sz; i++) {
			if (i == 0) {
				mx[i] = 1;
			} else {
				if (s[i] == s[i - 1]) {
					mx[i] = mx[i - 1] + 1;
				} else {
					mx[i] = 1;
				}
			}

			mx_len[s[i] - 'a'] = max(mx[i], mx_len[s[i] - 'a']);
		}
		suf_num = mx[sz - 1];
		only_one = false;
		int now = 0;
		while (now < sz && s[now] == s[0]) now++;
		pre_num = now;
		if (now == sz) only_one = true;
	}
	void my_union(Node& a) {
		// 要把自己加到 a 里面
		// 特判自己只有一个字符
		if (only_one) {
			int val = mx_len[s[0] - 'a'];
			mx_len[s[0] - 'a'] = min(1LL * (val + 1) * a.mx_len[s[0] - 'a'] + val, 1LL * inf);

			// 其他的点都会被拆开
			for (int i = 0; i < 26; i++) {
				if (s[0] - 'a' == i) continue;
				mx_len[i] = min(1, a.mx_len[i]);
			}
			// 计算 pre_num
			pre = s[0];
			if (a.pre == pre) {
				pre_num = min(1LL * (pre_num + 1) * a.pre_num, 1LL * inf);
			}
			// 计算 suf_num
			suf = s[s.size() - 1];
			if (a.suf == suf) {
				suf_num = min(1LL * (suf_num + 1) * a.suf_num, 1LL * inf);
			}

			if (a.only_one && a.pre == pre) {
				only_one = true;
			} else {
				only_one = false;
			}
		} else {
			// 计算 pre_num
			// 保持原样

			// 计算 suf_num
			// 保持原样

			// 计算 mx_len
			if (pre == suf) {

				if (a.mx_len[pre - 'a'] > 0) {
					mx_len[pre - 'a'] = min(max(mx_len[pre - 'a'], 1 + pre_num + suf_num), inf);
				}
				for (int i = 0; i < 26; i++) {
					if (pre - 'a' == i) continue;
					mx_len[i] = max({ mx_len[i], min(1, a.mx_len[i]) });
				}
			} else {
				if (a.mx_len[pre - 'a'] > 0) {
					mx_len[pre - 'a'] = max(mx_len[pre - 'a'], 1 + pre_num);
				}
				if (a.mx_len[suf - 'a'] > 0) {
					mx_len[suf - 'a'] = max(mx_len[suf - 'a'], 1 + suf_num);
				}
				for (int i = 0; i < 26; i++) {
					if (pre - 'a' == i) continue;
					if (suf - 'a' == i) continue;
					mx_len[i] = max({ mx_len[i], min(1, a.mx_len[i]) });
				}
			}
		}
	}
};
vector< Node > nodes;

int main() {
#ifdef LOCAL
	freopen("data.in", "r", stdin);
#endif
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n;
	cin >> n;
	nodes.resize(n + 1);
	for (int i = 1; i <= n; i++) {
		cin >> nodes[i].s;
		nodes[i].work();
	}

	for (int i = 2; i <= n; i++) {
		nodes[i].my_union(nodes[i - 1]);
		// nodes[i].out();
	}

	int res = 0;
	for (int i = 0; i < 26; i++) {
		res = max(res, nodes[n].mx_len[i]);
	}
	cout << res << endl;
	return 0;
}